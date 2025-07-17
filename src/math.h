/**
 * @file math.h
 * Math utilities.
 *
 * @author DannyXjsu
 * @version 1.0
 * @date 2025-07-15
 */

#ifndef MATH_H_
#define MATH_H_

/**
 * Vector2 structure.
 *
 * Represents a 2D vector with x and y components, can be accessed as an array.
 */
typedef struct {
    union {
        struct {
            /** The x component of the vector. */
            float x;
            /** The y component of the vector. */
            float y;
        };
        struct {
            /** The width of the rectangle. */
            float w;
            /** The height of the rectangle. */
            float h;
        };
        /** Array representation of the vector.*/
        float v[2];
    };
} Vector2;

/**
 * Calculates the length of the vector.
 *
 * Args:
 *     vector: The vector to calculate the length of.
 *
 * Returns:
 *     The length of the vector.
 */
extern float length(Vector2 *vector);

/**
 * Normalizes the vector.
 *
 * Args:
 *     vector: The vector to normalize.
 *
 * Returns:
 *     The normalized vector.
 */
extern Vector2 normalize(Vector2 *vector);

/**
 * Calculates the dot product of two vectors.
 *
 * Args:
 *     vector1: The first vector.
 *     vector2: The second vector.
 *
 * Returns:
 *     The dot product of the two vectors.
 */
extern float dot(Vector2 *vector1, Vector2 *vector2);

/**
 * Inverts a integer number.
 *
 * Args:
 *     num: The number to invert.
 *
 * Returns:
 *     The inverted number.
 */
extern int inverti(int num);

/**
 * Inverts a floating-point number.
 *
 * Args:
 *     num: The number to invert.
 *
 * Returns:
 *     The inverted number.
 */
extern float invertf(float num);

/**
 * Inverts a double number.
 *
 * Args:
 *     num: The number to invert.
 *
 * Returns:
 *     The inverted number.
 */
extern double invertd(double num);

/**
 * Overload function.
 *
 * Inverts a number.
 *
 * Args:
 *     num: The number to invert.
 *
 * Returns:
 *     The inverted number.
 */
#define invert(num) _Generic((num), int: inverti, float: invertf, double: invertd)(num)

/**
 * Clamps a integer value between a minimum and maximum value.
 *
 * Args:
 *     n: The value to clamp.
 *     min: The minimum value.
 *     max: The maximum value.
 *
 * Returns:
 *      The clamped value.
 */
extern int clampi(int n, int min, int max);

/**
 * Clamps a float value between a minimum and maximum value.
 *
 * Args:
 *     n: The value to clamp.
 *     min: The minimum value.
 *     max: The maximum value.
 *
 * Returns:
 *     The clamped value.
 */
extern float clampf(float n, float min, float max);

/**
 * Clamps a double value between a minimum and maximum value.
 *
 * Args:
 *     n: The value to clamp.
 *     min: The minimum value.
 *     max: The maximum value.
 *
 * Returns:
 *     The clamped value.
 */
extern double clampd(double n, double min, double max);

/**
 * Overload function.
 *
 * Clamps a value between a minimum and maximum value.
 *
 * Args:
 *     n: The value to clamp.
 *     min: The minimum value.
 *     max: The maximum value.
 *
 * Returns:
 *     The clamped value.
 */
#define clamp(n, min, max) _Generic((n, min, max), int: clampi, float: clampf, double: clampd)(n, min, max)

#endif // MATH_H_
