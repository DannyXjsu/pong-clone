/**
 * @file math.h
 * @brief Math utilities.
 *
 * @author DannyXjsu
 * @version 1.0
 * @date 2025-07-15
 */

#ifndef MATH_H_
#define MATH_H_

/**
 * @brief Vector2 structure.
 *
 * Represents a 2D vector with x and y components, can be accessed as an array.
 *
 * @param x The x component of the vector.
 * @param y The y component of the vector.
 * @param w The width of the rectangle.
 * @param h The height of the rectangle.
 * @param v Array representation of the vector.
 */
typedef struct {
    union {
        struct {
            float x;
            float y;
        };
        struct {
            float w;
            float h;
        };
        float v[2];
    };
} Vector2;

/**
 * @brief Calculates the length of the vector.
 *
 * @param vector The vector to calculate the length of.
 * @return The length of the vector.
 */
extern float length(Vector2 *vector);
/**
 * @brief Normalizes the vector.
 *
 * @param vector The vector to normalize.
 * @return The normalized vector.
 */
extern Vector2 normalize(Vector2 *vector);
/**
 * @brief Calculates the dot product of two vectors.
 *
 * @param vector1 The first vector.
 * @param vector2 The second vector.
 * @return The dot product of the two vectors.
 */
extern float dot(Vector2 *vector1, Vector2 *vector2);
/**
 * @brief Inverts a floating-point number.
 *
 * @param num The number to invert.
 * @return The inverted number.
 */
extern float invertf(float num);

#endif // MATH_H_
