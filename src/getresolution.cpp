#include "../includes/declarations.h"

//Function to get output from stdout.
string GetStdoutFromCommand(string cmd) 
{
    string data;
    FILE * stream;
    
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");

    if (stream) {
    const int max_buffer = 256;
    char buffer[max_buffer];
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
    }
    
    return data;
}

//Function to retrieve current system resolution. This is later used to draw appropriately sized circles and lines.
void findresolution()
{
    string s = "xrandr|grep '*'";
    string p = GetStdoutFromCommand(s);
    char width[4], height[4];
    int temp,i;

    for(i=0;i<p.size();i++)
        if(p[i]=='x')
            break;

    temp=i;
    i--;
    temp++;
    int d=3;

    while(p[i]!=' ')
        width[d--] = p[i--];

    d=0;

    while(p[temp]!=' ')
        height[d++] = p[temp++];

    WIDTH = atoi(width);
    HEIGHT = atoi(height);
}
