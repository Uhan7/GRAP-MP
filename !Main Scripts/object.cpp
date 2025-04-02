#include "object.h"

Object::Object(const std::string& objPath, const std::string& texturePath, int textureNumber, std::string imageType, float objectScale){
    // Load our OBJ
    std::string path = objPath;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;
    tinyobj::attrib_t attributes;

    bool objLoadSuccess = tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, path.c_str());
    if (!objLoadSuccess) std::cout << "Error! Object Loading Failed." << std::endl;

    for (size_t i = 0; i < attributes.vertices.size(); i++) {
        attributes.vertices[i] *= objectScale;
    }

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++){
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);

        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 2]);

        // Check if normals exist before accessing them
        if (!attributes.normals.empty()) {
            fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
            fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 1]);
            fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 2]);
        } else {
            fullVertexData.push_back(0.0f);
            fullVertexData.push_back(0.0f);
            fullVertexData.push_back(0.0f);
        }

        // Check if UVs exist before accessing them
        if (!attributes.texcoords.empty()) {
            fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
            fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2) + 1]);
        } else {
            fullVertexData.push_back(0.0f);
            fullVertexData.push_back(0.0f);
        }
    }
    // Load our Textures
    int img_width, img_height, colorChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* tex_bytes = stbi_load(texturePath.c_str(), &img_width, &img_height, &colorChannels, 0);

    GLuint texture;
    glGenTextures(1, &texture);

    switch(textureNumber){
        case 0: glActiveTexture(GL_TEXTURE0); break;
        case 1: glActiveTexture(GL_TEXTURE1); break;
        case 2: glActiveTexture(GL_TEXTURE2); break;
        case 3: glActiveTexture(GL_TEXTURE3); break;
    }

    glBindTexture(GL_TEXTURE_2D, texture);

    if (imageType == "RGB") glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes);
    else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_bytes);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes);

    glEnable(GL_DEPTH_TEST);

    // Object's VAO VBO Magic, VAO was already defined outside
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData.size(), fullVertexData.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    GLintptr normalPtr = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtr);

    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)uvPtr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object::~Object(){}

void Object::SetForward(glm::vec3 newForward){
    forwardDirection = newForward;
}

void Object::SetPosition(glm::vec3 newPositionVector){
    objectTranslationVector = newPositionVector;
}

void Object::SetScale(glm::vec3 newScaleVector){
    objectScaleVector = newScaleVector;
}

void Object::SetRotation(glm::vec3 newRotationEulerAngles){
    objectRotationQuaternion = glm::quat(glm::radians(newRotationEulerAngles));
}

void Object::Translate(char inputDirection, float translateSpeed){
    switch (inputDirection){
        case 'L': objectTranslationVector -= glm::vec3(translateSpeed, 0.0f, 0.0f); break;
        case 'R': objectTranslationVector += glm::vec3(translateSpeed, 0.0f, 0.0f); break;
        case 'D': objectTranslationVector -= glm::vec3(0.0f, translateSpeed, 0.0f); break;
        case 'U': objectTranslationVector += glm::vec3(0.0f, translateSpeed, 0.0f); break;
        case 'B': objectTranslationVector += glm::vec3(0.0f, 0.0f, translateSpeed); break;
        case 'F': objectTranslationVector -= glm::vec3(0.0f, 0.0f, translateSpeed); break;
        default: std::cout << inputDirection << " is not a valid Object Translation inputDirection." << std::endl; break;
    }
}

void Object::Translate(char inputDirection){
    switch (inputDirection){
        case 'L': objectTranslationVector -= glm::vec3(objectTranslateSpeed, 0.0f, 0.0f); break;
        case 'R': objectTranslationVector += glm::vec3(objectTranslateSpeed, 0.0f, 0.0f); break;
        case 'D': objectTranslationVector -= glm::vec3(0.0f, objectTranslateSpeed, 0.0f); break;
        case 'U': objectTranslationVector += glm::vec3(0.0f, objectTranslateSpeed, 0.0f); break;
        case 'B': objectTranslationVector += glm::vec3(0.0f, 0.0f, objectTranslateSpeed); break;
        case 'F': objectTranslationVector -= glm::vec3(0.0f, 0.0f, objectTranslateSpeed); break;
        default: std::cout << inputDirection << " is not a valid Object Translation inputDirection." << std::endl; break;
    }
}

void Object::Scale(bool enlarge){
    if (enlarge) objectScaleVector *= objectScaleSpeed;
    else objectScaleVector /= objectScaleSpeed;
}

void Object::Rotate(char polarity, char axis){
    // objectRotateSpeed = glm::radians(rotationSpeed);

    if (polarity == '+'){
        switch (axis){
            case 'X': objectRotationQuaternion = glm::inverse(qx) * objectRotationQuaternion; break;
            case 'Y': objectRotationQuaternion = glm::inverse(qy) * objectRotationQuaternion; break;
            case 'Z': objectRotationQuaternion = qz * objectRotationQuaternion; break;
            default: break;
        }
    }
    else if (polarity == '-'){
        switch (axis){
            case 'X': objectRotationQuaternion = qx * objectRotationQuaternion; break;
            case 'Y': objectRotationQuaternion = qy * objectRotationQuaternion; break;
            case 'Z': objectRotationQuaternion = glm::inverse(qz) * objectRotationQuaternion; break;
            default: break;
        }
    }
}

void Object::MoveForward(){
    objectTranslationVector += forward * objectTranslateSpeed;
}

void Object::MoveForward(float moveSpeed){
    objectTranslationVector += forward * moveSpeed;
}

void Object::Update(unsigned int shaderProgram, const GLchar* transformName, int transformNumber){
    forward = objectRotationQuaternion * forwardDirection;

    ObjectTransformationMatrix = glm::translate(glm::mat4(1.0f), objectTranslationVector);
    ObjectTransformationMatrix = glm::scale(ObjectTransformationMatrix, objectScaleVector);
    ObjectTransformationMatrix *= glm::mat4_cast(objectRotationQuaternion);

    unsigned int uniformTransformLocation = glGetUniformLocation(shaderProgram, transformName);
    glUniformMatrix4fv(uniformTransformLocation, 1, GL_FALSE, glm::value_ptr(ObjectTransformationMatrix));

    unsigned int uniformTransformNum = glGetUniformLocation(shaderProgram, "transformNumber");
    glUniform1i(uniformTransformNum, transformNumber);
}

void Object::Render(unsigned int shaderProgram, int textureNumber, int transformNumber){
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    GLuint uniformTransformLocation = glGetUniformLocation(shaderProgram, "transformNumber");
    glUniform1i(uniformTransformLocation, transformNumber);

    GLuint selectTex = glGetUniformLocation(shaderProgram, "textureNumber");
    if (textureNumber == 0){
        glActiveTexture(GL_TEXTURE0);
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");
        glUniform1i(tex0Address, 0);
        glUniform1i(selectTex, 0);
    }
    else if (textureNumber == 1){
        glActiveTexture(GL_TEXTURE1);
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex1");
        glUniform1i(tex0Address, 1);
        glUniform1i(selectTex, 1);
    }
    else if (textureNumber == 2){
        glActiveTexture(GL_TEXTURE2);
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex2");
        glUniform1i(tex0Address, 2);
        glUniform1i(selectTex, 2);
    }
    else if (textureNumber == 3){
        glActiveTexture(GL_TEXTURE3);
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex3");
        glUniform1i(tex0Address, 3);
        glUniform1i(selectTex, 3);
    }

    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size()/8);
}

glm::vec3 Object::GetPosition(){
    return objectTranslationVector;
}

glm::vec3 Object::GetScale(){
    return objectScaleVector;
}

glm::vec3 Object::GetRotation(){
    return glm::degrees(glm::eulerAngles(objectRotationQuaternion));
}

std::vector<GLfloat> Object::GetFullVertexData(){
    return fullVertexData;
}

glm::vec3 Object::GetObjectTranslationVector(){
    return objectTranslationVector;
}