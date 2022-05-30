#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Path.h"


template <class TVertex, class TEdge>
class Graph
{
	private:
        std::vector<TVertex> vertex;
        std::vector<Path<TVertex, TEdge>> ways;
        bool Find_Vertex(const TVertex& v) const
        {
            for (int i = 0; i < vertex.size(); i++)
                if (vertex[i] == v)
                    return true;
            return false;
        }
        int Index_by_Vertex(const TVertex& v) const
        {
            for (int i = 0; i < vertex.size(); i++)
                if (vertex[i] == v)
                    return i;
            return -1;
        }
        void Delete_Path(const TVertex& v)
        {
            for (int i = 0; i < ways.size(); i++)
                if ((v == ways[i].Source()) || (v == ways[i].Destination())) 
                {
                    ways.erase(ways.begin() + i);
                    i--;
                }
        }

	public:
        void Add_Vertex(const TVertex& v)
        {
            if (!Find_Vertex(v))
                vertex.push_back(v);
        }
        void Add(const TVertex& source, const TVertex& destination, const TEdge& edge)
        {
            Add_Edge(Path<TVertex, TEdge>(source, destination, edge));
        }
        void Add_Edge(const Path<TVertex, TEdge>& way)
        {
            ways.push_back(way);

            if (!Find_Vertex(way.Source())) {
                vertex.push_back(way.Source());
            }
            if (!Find_Vertex(way.Destination())) {
                vertex.push_back(way.Destination());
            }
        }
};