class Solution 
{
    private:
        inline bool GCD_GreaterThan1(int N1, int N2) const noexcept
        {
            while(N1 != N2)
            {
                if(N1 > N2) N1 -= N2;
                else N2 -= N1;
            }
            if(N1 > 1)
                return true;
            return false;
        }   // GCD_GreaterThan1
        
        inline int GetAdjVertex(int Ver) noexcept
        {
            int E = 0;
            for(int i = 0; i < Edges.size(); i++)
            {
                if(Edges[i].first == Ver)
                    E = Edges[i].second;
                
                for(int j = 0; j < Vertexes.size(); j++)
                {
                    if(Vertexes[j].first == E && !Vertexes[j].second)
                    {
                        Vertexes[j].second = true;
                        return Vertexes[j].first;
                    }
                }   // for
            }   // for
            return -1;
        }
    
        inline int MST() noexcept
        {
            set<int> St;
            Vertexes[Start].second = true;
            S.push(Vertexes[Start].first);
            
            while(!S.empty())
            {
                int CurrVertex = S.top();
                int v = GetAdjVertex(CurrVertex);
                if(v == -1)
                    S.pop();
                else
                {
                    S.push(v);
                    St.insert(CurrVertex);
                    St.insert(v);
                }
            }
            return St.size();
        }
        vector< pair<int,int> > Edges;
        vector< pair<int,bool> > Vertexes;
        stack<int> S;
        vector<int> StartV;
        int Start = 0;
    public:
        inline int largestComponentSize(vector<int> &Nodes) noexcept
        {
            //  Create Graph
            for(int i = 0; i < Nodes.size() - 1; i++)
            {
                Vertexes.push_back({Nodes[i], false});
                StartV.push_back(0);
                for(int j = i + 1; j < Nodes.size(); j++)
                    if(GCD_GreaterThan1(Nodes[i], Nodes[j]))
                    {
                        StartV[i]++;
                        Edges.push_back({Nodes[i], Nodes[j]});
                        Edges.push_back({Nodes[j], Nodes[i]});
                    }
            }
            Vertexes.push_back({Nodes[Nodes.size() - 1], false});
            Start = max_element(StartV.begin(),StartV.end()) - StartV.begin();
            
            return MST();
        }
};
