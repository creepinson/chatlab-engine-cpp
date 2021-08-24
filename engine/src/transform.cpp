#include <chatlab/transform.h>

Transform::Transform(Transform &other) {
    // copy transform values
    position = other.position;
    rotation = other.rotation;
    size = other.size;
}

Transform::Transform() {
    // set default values using glm
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    size = glm::vec3(1, 1, 1);
}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    this->position = position;
    this->rotation = rotation;
    this->size = scale;
}
Transform::Transform(glm::vec3 position, glm::vec3 rotation) {
    this->position = position;
    this->rotation = rotation;
}
Transform::Transform(glm::vec3 position) { this->position = position; }

glm::mat4 Transform::getMatrix() {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 translationMatrix = glm::translate(modelMatrix, position);
    glm::mat4 rotationX =
        glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
    glm::mat4 rotationY =
        glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
    glm::mat4 rotationZ =
        glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));
    glm::mat4 scaleMatrix = glm::scale(modelMatrix, size);
    return translationMatrix * rotationX * rotationY * rotationZ * scaleMatrix;
}

void Transform::translate(glm::vec3 translation) { position += translation; }
void Transform::rotate(glm::vec3 rotation) { rotation += rotation; }
void Transform::scale(glm::vec3 size) { size += size; }

void Transform::setPosition(glm::vec3 position) { this->position = position; }
void Transform::setRotation(glm::vec3 rotation) { this->rotation = rotation; }
void Transform::setSize(glm::vec3 size) { this->size = size; }
