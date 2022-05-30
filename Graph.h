#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Path.h"


template <class TVertex>
struct Result_BellmanFord
{
    double weight;
    std::vector<TVertex> path;

    Result_BellmanFord() 
    {
        weight = 0;
    }
    Result_BellmanFord(const double w, const std::vector<TVertex> p)
    {
        weight = w;
        path = p;
    }
};

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
                if (v == ways[i].Source() || v == ways[i].Destination()) 
                {
                    ways.erase(ways.begin() + i);
                    i--;
                }
        }
        std::vector<TVertex> Path_Recovery(std::vector<int> v, int start, int end) const
        {
            std::vector<int> res;
            res.push_back(end);
            int pred = end;
            while (pred != start)
            {
                int tmp = v[pred];
                res.push_back(tmp);
                pred = tmp;
            }
            std::vector<TVertex> names;
            for (int i = res.size() - 1; i >= 0; i--)
                names.push_back(vertex[res[i]]);
            return names;
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
            if (!Find_Vertex(way.Source()))
                vertex.push_back(way.Source());
            if (!Find_Vertex(way.Destination()))
                vertex.push_back(way.Destination());
        }
        void Delete_Vertex(const TVertex& v)
        {
            int index = Index_by_Vertex(v);
            if (index == -1)
                return;
            vertex.erase(vertex.begin() + index);
            Delete_Path(v);
        }
        void Delete_Edge(const TVertex& source, const TVertex& destination, const TEdge& edge)
        {
            for (int i = 0; i < ways.size(); i++)
                if (edge == ways[i].Edge() && source == ways[i].Source() && destination == ways[i].Destination())
                {
                    ways.erase(ways.begin() + i);
                    return;
                }
        }
        Result_BellmanFord<TVertex> BellmanFord(const TVertex& source, const TVertex& destination) const
        {
            if (Index_by_Vertex(destination) == -1)
                return Result_BellmanFord<TVertex>();
            std::vector<int> min_paths(vertex.size());
            std::fill(min_paths.begin(), min_paths.end(), INT_MAX);
            min_paths[Index_by_Vertex(source)] = 0;

            std::vector<double> temp(vertex.size());
            std::fill(temp.begin(), temp.end(), INFINITY);
            temp[Index_by_Vertex(source)] = 0;

            for (int i = 1; i < vertex.size(); i++)
            {
                for (int j = 0; j < ways.size(); j++)
                {
                    int tmp_source = Index_by_Vertex(ways[j].Source());
                    int tmp_destination = Index_by_Vertex(ways[j].Destination());
                    double tmp_weight = static_cast<double>(ways[j].Edge());
                    if (temp[tmp_destination] > temp[tmp_source] + tmp_weight)
                    {
                        temp[tmp_destination] = temp[tmp_source] + tmp_weight;
                        min_paths[tmp_destination] = tmp_source;
                    }
                }
            }
            if (temp[Index_by_Vertex(destination)] == INFINITY)
                return Result_BellmanFord<TVertex>();
            return Result_BellmanFord<TVertex>(temp[Index_by_Vertex(destination)], Path_Recovery(min_paths, Index_by_Vertex(source), Index_by_Vertex(destination)));
        }
        std::vector<std::pair<TVertex, TVertex>> Breadth_First_Search(const TVertex& source) const
        {
            std::vector<std::pair<TVertex, TVertex>> res;
            std::queue<TVertex> q;
            q.push(source);
            std::vector<int> used(vertex.size());
            std::fill(used.begin(), used.end(), 0);
            while (!q.empty())
            {
                TVertex v = q.front();
                used[Index_by_Vertex(v)] = 2;
                q.pop();
                for (int i = 0; i < ways.size(); i++)
                {
                    int dest = Index_by_Vertex(ways[i].Destination());
                    if (ways[i].Source() == v && used[dest] != 2)
                    {
                        res.push_back(std::pair<TVertex, TVertex>(v, ways[i].Destination()));
                        if (used[dest] != 1)
                        {
                            used[dest] = 1;
                            q.push(ways[i].Destination());
                        }
                    }
                }
            }
            return res;
        }
};