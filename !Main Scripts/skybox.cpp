#include "skybox.h"

Skybox::Skybox(int skyboxFaceNumber){
    // First determine which skybox to use

    for (int i = 0; i < 24; i++) this->vertices[i] = vertices[i];
    for (int i = 0; i < 36; i++) this->indices[i] = indices[i];

    switch (skyboxFaceNumber)
    {
        case 0: for (int i = 0; i < 6; i++) faces[i] = skyboxFace0[i]; break;
        case 1: for (int i = 0; i < 6; i++) faces[i] = skyboxFace1[i]; break;
        case 2: for (int i = 0; i < 6; i++) faces[i] = skyboxFace2[i]; break;
        
        default:
            cout << "ERROR: Can't find skybox face number " << skyboxFaceNumber << ". Reverting to default skybox 0." << endl;
            for (int i = 0; i < 6; i++) faces[i] = skyboxFace0[i];
                break;
    }

    // Now the actual creation of skybox
    
    glGenTextures(1, &skyboxTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++){
        int w, h, skyChannel;
        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(faces[i].c_str(),
            &w,
            &h,
            &skyChannel,
            0
        );

        if (data){
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                w,
                h,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
        }
        stbi_image_free(data);
    }

    stbi_set_flip_vertically_on_load(true);

    // skybox - VBO, VAO, and EBO Magic
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);

    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
}

void Skybox::Render(unsigned int skyboxShaderProgram, Camera* activeCameraPointer){
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShaderProgram);

        glm::mat4 skyboxViewMatrix = glm::mat4(1.f);
        skyboxViewMatrix = glm::mat4(glm::mat3(activeCameraPointer->GetCameraViewMatrix()));

        unsigned int uniformSkyboxViewLocation = glGetUniformLocation(skyboxShaderProgram, "view");
        glUniformMatrix4fv(uniformSkyboxViewLocation, 1, GL_FALSE, glm::value_ptr(skyboxViewMatrix));
        
        unsigned int uniformSkyboxProjectionLocation = glGetUniformLocation(skyboxShaderProgram, "projection");
        glUniformMatrix4fv(uniformSkyboxProjectionLocation, 1, GL_FALSE, glm::value_ptr(activeCameraPointer->GetCameraProjectionMatrix()));

        // Rendering Skybox
        glDepthMask(GL_FALSE);
        glUseProgram(skyboxShaderProgram);
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
}

void Skybox::ChangeFaces(int skyboxFaceNumber){
    switch (skyboxFaceNumber)
    {
        case 0: for (int i = 0; i < 6; i++) faces[i] = skyboxFace0[i]; break;
        case 1: for (int i = 0; i < 6; i++) faces[i] = skyboxFace1[i]; break;
        case 2: for (int i = 0; i < 6; i++) faces[i] = skyboxFace2[i]; break;
        
        default:
            cout << "ERROR: Can't find skybox face number " << skyboxFaceNumber << ". Reverting to default skybox 0." << endl;
            for (int i = 0; i < 6; i++) faces[i] = skyboxFace0[i];
                break;
    }

    // Now the actual creation of skybox
    
    glGenTextures(1, &skyboxTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++){
        int w, h, skyChannel;
        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(faces[i].c_str(),
            &w,
            &h,
            &skyChannel,
            0
        );

        if (data){
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                w,
                h,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
        }
        stbi_image_free(data);
    }

    stbi_set_flip_vertically_on_load(true);

    // skybox - VBO, VAO, and EBO Magic
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);

    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
}