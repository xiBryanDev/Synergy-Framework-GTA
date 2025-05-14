#pragma once
#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP
//#include "stdafx.h"


namespace math {

    // Classe vec2_t
    class vec2_t {
    public:
        union {
            struct { float x, y; };
            struct { float u, v; };
            float data[2];
        };

        vec2_t(float x = 0.0f, float y = 0.0f);
        float dot(const vec2_t& other) const;
        float length() const;
        vec2_t normalize() const;

        vec2_t operator+(const vec2_t& other) const;
        vec2_t operator-(const vec2_t& other) const;
        vec2_t operator*(float scalar) const;
        vec2_t operator/(float scalar) const;

        float& operator[](int index);
        const float& operator[](int index) const;

        bool operator==(const vec2_t& other) const {
            return x == other.x && y == other.y;
        }
    };

    // Classe vec3_t
    class vec3_t {
    public:
        union {
            struct { float x, y, z; };
            struct { float r, g, b; };
            float data[3];
        };

        vec3_t(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        float dot(const vec3_t& other) const;
        vec3_t cross(const vec3_t& other) const;
        float length() const;
        vec3_t normalize() const;

        vec3_t operator+(const vec3_t& other) const;
        vec3_t operator-(const vec3_t& other) const;
        vec3_t operator*(float scalar) const;
        vec3_t operator/(float scalar) const;

        float& operator[](int index);
        const float& operator[](int index) const;

        // Adicionado operador ==
        bool operator==(const vec3_t& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
    };
    // Classe vec4_t
    class vec4_t {
    public:
        union {
            struct { float x, y, z, w; };
            struct { float r, g, b, a; };
            float data[4];
        };

        vec4_t(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
        vec4_t(const vec3_t& xyz, float w = 1.0f);
        float dot(const vec4_t& other) const;
        float length() const;
        vec4_t normalize() const;

        vec3_t xyz() const;
        vec2_t xy() const;

        vec4_t operator+(const vec4_t& other) const;
        vec4_t operator-(const vec4_t& other) const;
        vec4_t operator*(float scalar) const;
        vec4_t operator/(float scalar) const;

        float& operator[](int index);
        const float& operator[](int index) const;
    };

    class Color {
    public:
        union {
            struct { int r, g, b, a; };
            int data[4];
        };

        Color(int r = 0, int g = 0, int b = 0, int a = 255);
        Color(const vec3_t& rgb, int a = 255); // Construtor a partir de vec3_t
        Color(const vec4_t& rgba); // Construtor a partir de vec4_t

        Color operator+(const Color& other) const;
        Color operator-(const Color& other) const;
        Color operator*(float scalar) const; // Multiplicação por float para ajustar intensidade

        int& operator[](int index);
        const int& operator[](int index) const;

        bool operator==(const Color& other) const {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        vec3_t toVec3() const; // Converte para vec3_t (0.0-1.0)
        vec4_t toVec4() const; // Converte para vec4_t (0.0-1.0)
    };



}

#endif // VECTOR_HPP