#pragma once

#include <cmath>
#include "raylib.h"

namespace popo
{
    class Vector2D
    {
    public:
        Vector2D(double x, double y) : x(x), y(y) {}
        Vector2D() : x(0), y(0) {}

    public:
        double x;
        double y;

    public:
        // Addition operator
        Vector2D operator+(const Vector2D& other) const
        {
            return Vector2D(x + other.x, y + other.y);
        }

        // Subtraction operator
        Vector2D operator-(const Vector2D& other) const
        {
            return Vector2D(x - other.x, y - other.y);
        }

        // Multiplication operator
        Vector2D operator*(const double& scalar) const
        {
            return Vector2D(x * scalar, y * scalar);
        }

        // Division operator
        Vector2D operator/(const double& scalar) const
        {
            return Vector2D(x / scalar, y / scalar);
        }

        // Compound addition operator
        Vector2D& operator+=(const Vector2D& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        // Compound subtraction operator
        Vector2D& operator-=(const Vector2D& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        // Compound multiplication operator
        Vector2D& operator*=(const double& scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        // Compound division operator
        Vector2D& operator/=(const double& scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        // Magnitude function
        double magnitude() const
        {
            return std::sqrt(x * x + y * y);
        }

        // Normalize function
        Vector2D normalize() const
        {
            double mag = magnitude();
            return Vector2D(x / mag, y / mag);
        }

        // Normalize this vector
        void normalize_this()
        {
            double mag = magnitude();
            x /= mag;
            y /= mag;
        }

        operator Vector2() const
        {
            return { static_cast<float>(x), static_cast<float>(y) };
        }
    };

    class Vector3D
    {
    public:
        Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
        Vector3D() : x(0), y(0), z(0) {}

    public:
        double x;
        double y;
        double z;

    public:
        // Addition operator
        Vector3D operator+(const Vector3D& other) const
        {
            return Vector3D(x + other.x, y + other.y, z + other.z);
        }

        // Subtraction operator
        Vector3D operator-(const Vector3D& other) const
        {
            return Vector3D(x - other.x, y - other.y, z - other.z);
        }

        // Multiplication operator
        Vector3D operator*(const double& scalar) const
        {
            return Vector3D(x * scalar, y * scalar, z * scalar);
        }

        // Division operator
        Vector3D operator/(const double& scalar) const
        {
            return Vector3D(x / scalar, y / scalar, z / scalar);
        }

        // Compound addition operator
        Vector3D& operator+=(const Vector3D& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        // Compound subtraction operator
        Vector3D& operator-=(const Vector3D& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        // Compound multiplication operator
        Vector3D& operator*=(const double& scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        // Compound division operator
        Vector3D& operator/=(const double& scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        // Magnitude function
        double magnitude() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        // Normalize function
        Vector3D normalize() const
        {
            double mag = magnitude();
            return Vector3D(x / mag, y / mag, z / mag);
        }

        // Normalize this vector
        void normalize_this()
        {
            double mag = magnitude();
            x /= mag;
            y /= mag;
            z /= mag;
        }

        operator Vector3() const
        {
            return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
        }
    };
}
