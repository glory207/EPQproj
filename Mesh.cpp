#include "Mesh.h"

Mesh::Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures, string name)
{
    Mesh::name = name;
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

    VAO.Bind();
    VBO VBO(vertices);
    EBO EBO(indices);
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}
void Mesh::Draw(Shader& shader, Camera& camera)
{
    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;


    for (unsigned int i = 0; i < textures.size(); i++)
    {
        string num;
        string type = textures[i].type;
        if (type == "diffuse") {
            num = to_string(numDiffuse++);
        }else if (type == "specular") {
            num = to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    


}
Mesh::Mesh(string path , vector<Texture>& textures)
{
    Mesh::textures = textures;
    string line = "#";

    ifstream MyReadFile(path);
    int num = 0;

    vector <vec3> verts;
    vector <vec2> verTex;
    vector <Vertex> vertex;
    vector <GLuint> indices;
    vec3 offset(0, 0, 0);
    while (getline(MyReadFile, line)) {
        
        if (line.substr(0,2) == "o ")
        {
            
            
            name = line.substr(2, line.length()-2);
        

                num++;

        }
        else if (line.substr(0, 2) == ("v "))
        {
            
            float x;
            float y;
            float z;
            string temp = "";
            int start = 2;
            for (int i = start; i < line.length(); i++)
            {
                if (line[i] == ' ')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            x = stof(temp);
            temp = "";
            for (int i = start; i < line.length(); i++)
            {
                if (line[i] == ' ')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            y = stof(temp);
            temp = "";
            for (int i = start; i < line.length(); i++)
            {
                if (line[i] == ' ')
                {
                    break;
                }
                else
                {
                    temp += line[i];
                }
            }
            z = stof(temp);
            temp = "";
            verts.push_back(vec3(x, y, z));
        }
        else if (line.substr(0, 3) == ("vt "))
        {

            float x;
            float y;
            string temp = "";
            int start = 3;
            for (int i = start; i < line.length(); i++)
            {
                if (line[i] == ' ')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            x = stof(temp);
            temp = "";
            for (int i = start; i < line.length(); i++)
            {
                if (line[i] == ' ')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            y = stof(temp);
            temp = "";
            verTex.push_back(vec2(x,y));
        }
        else if (line.substr(0, 2) == ("f "))
        {

            int x;
            int y;
            int z;
            string temp = "";
            int start = 2;
            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == '/')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            x = stoi(temp);
            temp = "";
            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == '/')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            y = stoi(temp);
            temp = "";

            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == ' ')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            z = stoi(temp);
            temp = "";

            vertex.push_back(Vertex{ verts[x - 1 - offset.x],verTex[y - 1 - offset.y] });
            indices.push_back(vertex.size()-1);

            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == '/')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            x = stoi(temp);
            temp = "";
            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == '/')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            y = stoi(temp);
            temp = "";

            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == ' ')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            z = stoi(temp);
            temp = "";

            vertex.push_back(Vertex{ verts[x - 1 - offset.x],verTex[y - 1 - offset.y] });
            indices.push_back(vertex.size()-1);

            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == '/')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            x = stoi(temp);
            temp = "";
            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == '/')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            y = stoi(temp);
            temp = "";

            for (int i = start; i < line.length(); i++)
            {
                if ((line[i]) == ' ')
                {
                    start = i + 1; break;
                }
                else
                {
                    temp += line[i];
                }
            }
            z = stoi(temp);
            temp = "";
            vertex.push_back(Vertex{ verts[x - 1 - offset.x],verTex[y - 1 - offset.y] });
            indices.push_back(vertex.size()-1);
        }

    }

    Mesh::indices = indices;
    Mesh::vertices = vertex;

    MyReadFile.close();

    VAO.Bind();
    VBO VBO(vertices);
    EBO EBO(Mesh::indices);
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

Mesh::Mesh(){
    Mesh::name = "Empty";
    Mesh::vertices = { Vertex{vec3(0),vec3(0)} ,Vertex{vec3(0),vec3(0)} ,Vertex{vec3(0),vec3(0)} };
    Mesh::indices = {0,1,2};

    VAO.Bind();
    VBO VBO(vertices);
    EBO EBO(indices);
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}