#pragma once

class Quad : public GameObject
{
private:
    typedef VertexUV VertexType;

public:
    Quad(Vector2 size);    
    Quad(wstring file);
    ~Quad();

    void Render();
    void SetRender();

    Vector2 GetSize() { return size; }

    wstring GetFileName() { return fileName; }
private:
    void MakeMesh();

protected:
    Mesh<VertexType>* mesh;
    ColorBuffer* colorBuffer = nullptr;
    Vector2 size;

private:
    wstring fileName;
};