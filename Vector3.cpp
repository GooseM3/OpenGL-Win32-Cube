struct Vector3
{
    float x;
    float y;
    float z;

    static Vector3 UnitX()
    {
        return Vector3{ 1.0f, 0.0f, 0.0f };
    }

    static Vector3 Unity()
    {
        return Vector3{ 0.0f, 1.0f, 0.0f };
    }

    static Vector3 UnitZ()
    {
        return Vector3{ 0.0f, 0.0f, 1.0f };
    }

    Vector3 operator-()
    {
        return Vector3{ -x, -y, -z };
    }

    Vector3 operator+(Vector3& other)
    {
        return Vector3{ x + other.x, y + other.y, z + other.z };
    }

    Vector3 operator-(Vector3& other)
    {
        return Vector3{ x - other.x, y - other.y, z - other.z };
    }

    friend Vector3 operator/(Vector3& v, float value)
    {
        return Vector3{ v.x / value, v.y / value, v.z / value };
    }

    float Length()
    {
        return sqrtf(x * x + y * y + z * z);
    }

    Vector3 Normalized()
    {
        return *this / Length();
    }

    static Vector3 Cross(Vector3* a, Vector3* b)
    {
        return Vector3{
            a->y * b->z - a->z * b->y,
            a->z * b->x - a->x * b->z,
            a->x * b->y - a->y * b->x };
    }

    static Vector3 GetRight(Vector3* front)
    {
        Vector3 unity = Unity();
        return Cross(front, &unity).Normalized();
    }

    static Vector3 GetUp(Vector3* front, Vector3* right)
    {
        return Cross(right, front).Normalized();
    }
};
