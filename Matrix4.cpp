struct Matrix4
{
    float row0X, row1X, row2X, row3X;
    float row0Y, row1Y, row2Y, row3Y;
    float row0Z, row1Z, row2Z, row3Z;
    float row0W, row1W, row2W, row3W;

    Matrix4(
        float row0X, float row0Y, float row0Z, float row0W,
        float row1X, float row1Y, float row1Z, float row1W,
        float row2X, float row2Y, float row2Z, float row2W,
        float row3X, float row3Y, float row3Z, float row3W
    )
    {
        this->row0X = row0X;
        this->row0Y = row0Y;
        this->row0Z = row0Z;
        this->row0W = row0W;
        this->row1X = row1X;
        this->row1Y = row1Y;
        this->row1Z = row1Z;
        this->row1W = row1W;
        this->row2X = row2X;
        this->row2Y = row2Y;
        this->row2Z = row2Z;
        this->row2W = row2W;
        this->row3X = row3X;
        this->row3Y = row3Y;
        this->row3Z = row3Z;
        this->row3W = row3W;
    }

    friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
    {
        return Matrix4(
            a.row0X * b.row0X + a.row0Y * b.row1X + a.row0Z * b.row2X + a.row0W * b.row3X,
            a.row0X * b.row0Y + a.row0Y * b.row1Y + a.row0Z * b.row2Y + a.row0W * b.row3Y,
            a.row0X * b.row0Z + a.row0Y * b.row1Z + a.row0Z * b.row2Z + a.row0W * b.row3Z,
            a.row0X * b.row0W + a.row0Y * b.row1W + a.row0Z * b.row2W + a.row0W * b.row3W,

            a.row1X * b.row0X + a.row1Y * b.row1X + a.row1Z * b.row2X + a.row1W * b.row3X,
            a.row1X * b.row0Y + a.row1Y * b.row1Y + a.row1Z * b.row2Y + a.row1W * b.row3Y,
            a.row1X * b.row0Z + a.row1Y * b.row1Z + a.row1Z * b.row2Z + a.row1W * b.row3Z,
            a.row1X * b.row0W + a.row1Y * b.row1W + a.row1Z * b.row2W + a.row1W * b.row3W,

            a.row2X * b.row0X + a.row2Y * b.row1X + a.row2Z * b.row2X + a.row2W * b.row3X,
            a.row2X * b.row0Y + a.row2Y * b.row1Y + a.row2Z * b.row2Y + a.row2W * b.row3Y,
            a.row2X * b.row0Z + a.row2Y * b.row1Z + a.row2Z * b.row2Z + a.row2W * b.row3Z,
            a.row2X * b.row0W + a.row2Y * b.row1W + a.row2Z * b.row2W + a.row2W * b.row3W,

            a.row3X * b.row0X + a.row3Y * b.row1X + a.row3Z * b.row2X + a.row3W * b.row3X,
            a.row3X * b.row0Y + a.row3Y * b.row1Y + a.row3Z * b.row2Y + a.row3W * b.row3Y,
            a.row3X * b.row0Z + a.row3Y * b.row1Z + a.row3Z * b.row2Z + a.row3W * b.row3Z,
            a.row3X * b.row0W + a.row3Y * b.row1W + a.row3Z * b.row2W + a.row3W * b.row3W);
    }

    static Matrix4 LookAt(Vector3 position, Vector3 target)
    {
        Vector3 front = (position - target).Normalized();
        Vector3 mFront = -front;
        Vector3 right = Vector3::GetRight(&mFront);
        Vector3 up = Vector3::GetUp(&mFront, &right);

        return Matrix4{
            right.x, right.y, right.z, -(right.x * position.x + right.y * position.y + right.z * position.z),
            up.x, up.y, up.z, -(up.x * position.x + up.y * position.y + up.z * position.z),
            front.x, front.y, front.z, -(front.x * position.x + front.y * position.y + front.z * position.z),
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    static Matrix4 CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane)
    {
        float yScale = 1.0f / tanf(fov * 0.5f);
        float xScale = yScale / aspectRatio;

        return Matrix4(
            xScale, 0.0f, 0.0f, 0.0f,
            0.0f, yScale, 0.0f, 0.0f,
            0.0f, 0.0f, -(farPlane + nearPlane) / (farPlane - nearPlane), -farPlane * nearPlane * 2.f / (farPlane - nearPlane),
            0.0f, 0.0f, -1.0f, 0.f);
    }
};
