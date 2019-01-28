#include <glm/glm.hpp>

class Viewport{
public:

    glm::vec3 direction, right, up, position, focus;
    float theta, phi, radius;

    Viewport():direction(glm::vec3(0, 0, -1)), right(glm::vec3(1, 0, 0)), up(glm::vec3(0, 1, 0)), position(glm::vec3(0, 0, -1)), focus(glm::vec3(0, 0, 0)), theta(3.14 * 0.5f), phi(3.14 * 0.5f), radius(1.0f){
    }
    Viewport(glm::vec3 direction, glm::vec3 right, glm::vec3 up, glm::vec3 position, glm::vec3 focus, float theta, float phi, float radius): direction(direction), right(right), up(up), position(position), focus(focus), theta(theta), phi(phi), radius(radius){
    }

    glm::mat4 vMat() const;

    void rHorz(float rads);
    void rVert(float rads);
    void scale(float s);
    // void transformOne(glm::vec3 move);
    // void transformTwo(float dTheta, float dPhi);
    void transform(float dTheta, float dPhi);

  };
