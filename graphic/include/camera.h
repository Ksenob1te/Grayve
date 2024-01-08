#ifndef GRAYVE_CAMERA_H
#define GRAYVE_CAMERA_H

#include "cmath"
#include "entity.h"
#include "GL/glut.h"
#include "collider.h"

/**
 * @brief The Camera class manages the viewpoint and perspective in the game.
 */
class Camera {
private:
    double theta;         ///< Theta angle for camera orientation.
    double phi;           ///< Phi angle for camera orientation.
    Point coordinates;    ///< Coordinates of the camera.
    double height;        ///< Height of the camera from the ground.
    ColliderBox collider; ///< Collider box for the camera.

public:
    Entity* follow; ///< Entity to which the camera is following.

    /**
     * @brief Default constructor for the Camera class.
     */
    Camera(): theta(2.5 * M_PI / 4), phi(0), follow(nullptr) {
        coordinates = Point(0, 0);
        collider.set_center(&coordinates);
        collider.set_radius(5);
        height = 0;
    }

    /**
     * @brief Returns the X coordinate the camera is looking at.
     * @return The X coordinate.
     */
    [[nodiscard]] double getLookX() const { return follow->getX(); }

    /**
     * @brief Returns the Y coordinate the camera is looking at.
     * @return The Y coordinate.
     */
    [[nodiscard]] double getLookY() const { return follow->getY() + 2; }

    /**
     * @brief Returns the Z coordinate the camera is looking at.
     * @return The Z coordinate.
     */
    [[nodiscard]] double getLookZ() const { return follow->getZ(); }

    /**
     * @brief Returns the phi angle of the camera.
     * @return The phi angle.
     */
    [[nodiscard]] double getPhi() const { return this->phi; }

    /**
     * @brief Returns the theta angle of the camera.
     * @return The theta angle.
     */
    [[nodiscard]] double getTheta() const { return this->theta; }

    /**
     * @brief Returns the collider box of the camera.
     * @return The collider box.
     */
    [[nodiscard]] const ColliderBox& getCollider() const { return this->collider; }

    /**
     * @brief Sets the phi angle of the camera.
     * @param set_phi The phi angle to set.
     */
    void setPhi(double set_phi) {
        while (set_phi < -M_PI) set_phi += (2 * M_PI);
        while (set_phi > M_PI) set_phi -= (2 * M_PI);
        this->phi = set_phi;
    }

    /**
     * @brief Changes the theta angle of the camera by a specified amount.
     * @param amount The amount to change the theta angle.
     */
    void changeTheta(double amount) {
        if (theta + amount >= 6 * M_PI / 10 && theta + amount <= M_PI) theta += amount;
    }

    /**
     * @brief Updates the camera position and orientation.
     * @param interpolation The interpolation value for smooth updates.
     */
    void update(double interpolation);
};

#endif //GRAYVE_CAMERA_H
