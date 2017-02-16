//
//  main.cpp
//  pizzadelivery
//
//  Created by Sara Lindström on 2017-02-15.
//  Copyright © 2017 Sara Lindström. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Map
{
    int _width;
    int _height;
    vector< vector<int> > _map;
    
    Map(int width, int height)
    {
        _width = width;
        _height = height;
        vector< vector<int> > map(_height, vector<int>(_width));
        _map = map;
    }
    
    void setMap(const int x, const int y, const int value)
    {
        _map[y][x] = value;
    }
    
    const int getValue(const int x, const int y)
    {
        return _map[y][x];
    }
};

//Calculate delivery cost for entire map
int deliveryCost(Map& map)
{
    int width = map._width;
    int height = map._height;
    
    //For each street corner, "kitchen" calculate the cost for delivery to all other street corners and add to array "costs"
    int costs[width*height];
    for (int kitchenX = 0; kitchenX < width; ++kitchenX)
    {
        for (int kitchenY= 0; kitchenY < height; ++kitchenY)
        {
            int deliveryCost = 0;
            for (int deliveryY = 0; deliveryY < width; ++deliveryY)
            {
                for(int deliveryX = 0; deliveryX < height; ++deliveryX)
                {
                    deliveryCost += (abs(deliveryX - kitchenX) + abs(deliveryY - kitchenY)) * map.getValue(deliveryY, deliveryX);
                }
            }
            costs[(kitchenX + kitchenY*width)] = deliveryCost;
        }
    }
    
    // Get min in cost array that has cost for kitchen at each corner
    int min = costs[0];
    for (int i = 0; i < width*height; ++i)
    {
        if (costs[i] < min)
        {
            min = costs[i];
        }
    }
    return min;
}

int main(int argc, const char * argv[]) {
    
    //Read from file
    int line;
    vector<int> lines;
    while (cin >> line)
    {
        lines.push_back(line);
    }
    
    int cases = lines[0];
    int loaded = 0;
    int startCurrentCase = 1;
    while (loaded != cases)
    {
        int mapW = lines[startCurrentCase];
        int mapH = lines[startCurrentCase+1];
        Map map(mapW, mapH);
        int mapElement = startCurrentCase + 2;
        
        for (int y = 0; y < mapH; ++y)
        {
            for (int x = 0; x < mapW; ++x)
            {
                map.setMap(x, y, lines[mapElement]);
                ++mapElement;
            }
        }
        startCurrentCase += (mapW*mapH + 2);
        ++loaded;
        cout << deliveryCost(map) << " blocks" << endl;
    }
    return 0;
}
