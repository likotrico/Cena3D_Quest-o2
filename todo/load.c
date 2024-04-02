#include <stdbool.h>
#include <stdio.h>

int loadOBJ(const char *path,
            double **out_vertices,
            double **out_uvs,
            double **out_normals)
{
    double **temp_vertices;
    double **temp_uvs;
    double **temp_normals;

    unsigned int **vertexIndices;
    unsigned int **uvIndices;
    unsigned int **normalIndices;

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Impossible to open the file\n");
        return -1;
    }

    int k = 0;

    while (1)
    {
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        if (strcmp(lineHeader, "v") == 0)
        {
            fscanf(file,
                   "%f %f %f\n",
                   temp_vertices[k][0],
                   temp_vertices[k][1],
                   temp_vertices[k][2]);

            // else : parse lineHeader
        }
        else if (strcmp(lineHeader, "vt") == 0)
        {
            fscanf(file, "%f %f\n",
                   temp_uvs[k][0],
                   temp_uvs[k][1]);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            fscanf(file, "%f %f\n",
                   temp_normals[k][0],
                   temp_normals[k][1]);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file,
                                 "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            if (matches != 9)
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }

            vertexIndices[k][0] = vertexIndex[0];
            vertexIndices[k][1] = vertexIndex[1];
            vertexIndices[k][2] = vertexIndex[2];

            uvIndices[k][0] = uvIndex[0];
            uvIndices[k][1] = uvIndex[1];
            uvIndices[k][2] = uvIndex[2];

            normalIndices[k][0] = normalIndex[0];
            normalIndices[k][1] = normalIndex[1];
            normalIndices[k][2] = normalIndex[2];
        }

        k++;
    }

    unsigned int vertexIndex;
    double *vertex;

    for (unsigned int i = 0; i < k; i++)
    {
        vertexIndex = vertexIndices[i];
        vertex = temp_vertices[vertexIndex - 1];
        out_vertices = vertex;
    }
}