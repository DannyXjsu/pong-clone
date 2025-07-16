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
 * @brief Inverts a integer number.
 *
 * @param num The number to invert.
 * @return The inverted number.
 */
extern int inverti(int num);

/**
 * @brief Inverts a floating-point number.
 *
 * @param num The number to invert.
 * @return The inverted number.
 */
extern float invertf(float num);

/**
 * @brief Inverts a double number.
 *
 * @param num The number to invert.
 * @return The inverted number.
 */
extern double invertd(double num);

/**
 * @brief Inverts a number.
 *
 * @param num The number to invert.
 * @return The inverted number.
 */
#define invert(num) _Generic((num), int: inverti, float: invertf, double: invertd)(num)

/**
 * @brief Clamps a integer value between a minimum and maximum value.
 *
 * @param d The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
extern int clampi(int n, int min, int max);

/**
 * @brief Clamps a float value between a minimum and maximum value.
 *
 * @param d The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
extern float clampf(float n, float min, float max);

/**
 * @brief Clamps a double value between a minimum and maximum value.
 *
 * @param d The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
extern double clampd(double n, double min, double max);

/**
 * @brief Clamps a value between a minimum and maximum value.
 *
 * @param d The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
#define clamp(n, min, max) _Generic((n, min, max), int: clampi, float: clampf, double: clampd)(n, min, max)

#endif // MATH_H_
