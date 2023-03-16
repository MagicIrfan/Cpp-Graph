// BOUHENAF Irfan IP TP3
#include "Graph.hpp"

Graph::Graph()
{}

Graph::~Graph()
{}

void Graph::addVertex(int v)
{
    if(!containsVertex(v))                                                  //On insère dans le unordered_map si et seulement si le sommet passé en paramètre n'existe pas dans le graphe
    {
        std::unordered_set<int> temp;                                       //On crée un tableau vide temporaire afin de l'associer à une clé
        map.insert(std::pair<int,std::unordered_set<int>>(v,temp));         //Insertion de la clé passé en paramètre et du tableau de voisins de la clé dans le unordered_map
    }
}

void Graph::addEdge(int u,int v)
{
    addVertex(u);
    addVertex(v);
    if (containsVertex(v) && containsVertex(u))                             //On ajoute l'arête si et seulement si les sommet passés en paramètre existent dans le graphe
    {
        auto goodmapu = map.find(u);                                        //Endroit de la unordered_map où u est la clé
        auto goodmapv = map.find(v);                                        //Endroit de la unordered_map où v est la clé
        if (!goodmapu->second.count(v))
            goodmapu->second.insert(v);                                     //On insère u dans les voisins de v s'il n'existe pas
        if (!goodmapv->second.count(u))
            goodmapv->second.insert(u);                                     //On insère v dans les voisins de u s'il n'existe pas
    } 
        
}

bool Graph::containsVertex(int v) const
{
    bool pareil = false;
    if (map.count(v))
        pareil = true;
    return pareil;
}

bool Graph::containsEdge(int u,int v) const
{
    bool pareil = false;
    if (containsVertex(v) && containsVertex(u))
    {
        auto goodmapu = map.find(u);
        auto goodmapv = map.find(v);
        if ((goodmapu->second.count(v)) && (goodmapv->second.count(u)))   //Si et seulement si v est un voisin de u et u est un voisin de v
            pareil = true;
    }
    return pareil;
}

int Graph::degree(int v) const
{
    int neighbours = -1;
    if (containsVertex(v))
    {
        auto goodmapv = map.find(v);
        neighbours = goodmapv->second.size();
    }
    return neighbours;
}

int Graph::maxDegree() const
{
    int max = -1;
    for(auto it=map.begin() ; it!=map.end(); ++it)
    {
        if(degree(it->first) > max)
            max = degree(it->first);                                      //On compare tous les degrés des sommets avec max pour que max prenne la valeur maximale
    }
    return max;
}

int Graph::countVertices() const
{
    return map.size();
}

int Graph::countEdges() const
{
    int edges = 0;
    for(auto it=map.begin() ; it!=map.end(); ++it)
        edges+=it->second.size();                                        //On additionne tous les degrés des sommets avec edges en parcourant le graphe
    return edges/2;                                                      //On divisent cette somme par 2 car une arête est formée de deux voisins                                            
}

void Graph::removeEdge(int u, int v)
{
    if (containsEdge(u,v))
    {
        map.find(u)->second.erase(v);                                   //Le voisin v est effacé chez le sommet u                                
        map.find(v)->second.erase(u);                                   //Le voisin u est effacé chez le sommet v
    }
}

void Graph::removeVertex(int v)
{
    if (containsVertex(v))
    {
        auto goodmapv = map.find(v);
        for(auto it=map.begin() ; it!=map.end(); ++it)
        {
            if (it->second.count(v))
                it->second.erase(v);                                    //Le voisin v est effacé chez les sommets qu'ils le possèdent
        }
        goodmapv->second.clear();
        map.erase(v);
    }
    
}

void Graph::contract(int u, int v)
{
    if (containsVertex(u) && containsVertex(v))
    {
        auto goodmapu = map.find(u);
        auto goodmapv = map.find(v);
        for(auto it=goodmapv->second.begin() ; it!=goodmapv->second.end(); ++it)
            goodmapu->second.insert(*it);                              //Le voisin v est effacé chez les sommets qu'ils le possèdent           
        for(auto it=map.begin() ; it!=map.end(); ++it)
        {
            if(containsEdge(it->first,v))
                it->second.insert(u);                                  //Le voisin u est ajouté chez les sommets qui ont comme voisin v (qui sera supprimé à la fin de la fonction)   
        }
        removeVertex(v);
    }
}

std::vector<int> Graph::neighbors(int v) const
{
    std::vector<int> vec;
    if (containsVertex(v))
    {
        auto goodmapv = map.find(v);
        for(auto it=goodmapv->second.begin() ; it!=goodmapv->second.end(); ++it)
            vec.push_back(*it);                                       //Les voisins du sommet v sont ajoutés dans le vector grâce à la boucle for
        std::sort(vec.begin(), vec.end());                            //Tri à l'ordre croissant du vecteur
    }
    return vec;
}

std::vector<int> Graph::commonNeighbors(int u,int v) const
{
    std::vector<int> vec;
    if (containsVertex(v) && containsVertex(u))
    {
        for(auto it=map.begin() ; it!=map.end(); ++it)
        {
            if (containsEdge(u,it->first) && containsEdge(v,it->first))
                vec.push_back(it->first);                            //Les voisins commun de u et v sont insérés dans le vecteur grâce à la boucle for
        }
        
        std::sort(vec.begin(), vec.end());
    }
    return vec;
}

std::vector<int> Graph::dfs(int v) const
{
    std::vector<int> search;
    if (containsVertex(v))
    {
        std::map<int,bool> marking;                                 //Le tableau associatif marking permet de marquer un sommet déjà visité dans le graphe grâce à un booléen           
        for (auto it = map.begin(); it != map.end(); ++it)
            marking.insert(std::pair<int,bool>(it->first,false));   //Avant le parcours, les sommets ne sont pas marqués car ils ne sont pas visités, on remplit le tableau associatif en parcourant le graphe           
        search.push_back(v);                                        //v est déjà visité vu que c'est le sommet de départ
        marking.find(v)->second = true;                             //Donc il est marqué comme visité
        searchdfs(search,marking,v);                                //Définition de la méthode searchdfs qui est une méthode récursive afin de visiter les sommets du graphe
    }
    return search;
}

void Graph::searchdfs(std::vector <int> & search,std::map<int,bool> & marking, int v) const
{
    for (unsigned int i=0; i<neighbors(v).size(); ++i)              //Pour tous les voisins du sommet passé en paramètre
    {
        if (marking.count(neighbors(v).at(i)))                      
        {
            if (marking.find(neighbors(v).at(i))->second == false)  //Si le sommet n'est pas marqué
            {
                search.push_back(neighbors(v).at(i));               //On insère le sommet dans le vector
                marking.find(neighbors(v).at(i))->second = true;    //Le sommet est marqué
                searchdfs(search,marking,neighbors(v).at(i));       //Appel récursif de la méthode avec le sommet marqué comme paramètre qui explore le premier sommet voisin jusqu'à que le parcours soit fini
            }
        }                               
    }
        
}

std::vector<int> Graph::bfs(int v) const
{
    std::vector<int> search;
    if (containsVertex(v))
    {
        std::map<int,bool> marking;
        for (auto it = map.begin(); it != map.end(); ++it)
            marking.insert(std::pair<int,bool>(it->first,false));
        search.push_back(v);
        marking.find(v)->second = true;
        for(unsigned int i=0; i<search.size();++i)                
            searchbfs(search,marking, search.at(i));                //On commence par explorer le sommet de départ, puis ses voisins puis les voisins des voisins etc... jusqu'à que tous les sommets soient marqués          
    }
    return search;
}

void Graph::searchbfs(std::vector <int> & search, std::map<int,bool> & marking , int v) const
{
        for (unsigned int i=0; i<neighbors(v).size(); ++i)
        {
            if (marking.count(neighbors(v).at(i)))
            {
                if (marking.find(neighbors(v).at(i))->second == false)
                {
                    search.push_back(neighbors(v).at(i));
                    marking.find(neighbors(v).at(i))->second = true;
                }
            }
                                    
        }
}


