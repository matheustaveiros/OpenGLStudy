#pragma once

class Input
{
private:
    inline static bool _keys[1024];

public:
    static void SetKeyStatus(int key, bool isPressed){ _keys[key] = isPressed; }
    static bool GetKey(int key) { return _keys[key]; }
};