struct Vec2 {
    float x;
    float y;

    Vec2(float x, float y);
    Vec2 operator+(const Vec2& other);
    Vec2 operator-(const Vec2& other);

    float lenght();
    void normalize();
};