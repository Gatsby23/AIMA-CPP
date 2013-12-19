#ifndef NODE_TEST_HPP
#define NODE_TEST_HPP

#include <string>

#include <tuple>
#include <iostream>

using namespace std;

#include <stdio.h>
#include "search.hpp"

using namespace AI;

DefClassProblem(IntProblem, int)
{
    IntProblem()
    : Problem(10) 
    {
        auto &_40 = getRoot().connect1(40,50);
        _40.connect1(22);
        _40.connect1(23);
        auto &_12 = getRoot().connect1(12);
        _12.connect1(6);
        _12.connect1(8).connect1(7,4);
        _12.connect1(20);
        auto &_11 = getRoot().connect1(11,12);
        _11.connect1(9);
        _11.connect1(25).connect1(26);


        //
        //             ___10__
        //           /    |   \ 
        //         40    12_   11 ___
        //       / |    / | \    \  \
        //    22  23   6  8  20   9  25
        //                |           |
        //                7           26
        // 
        //  

    }

    bool isGoal (const int & value) const {
        return ( value == 7 );
    }
    
    long F(const node_ptr &n, const long &gn, const long &parent_cost) const 
    { return parent_cost + gn; }

};



DefClassProblem(TestProblem, int)
{
    TestProblem()
    : Problem(0)
    { }

    leafs_list successors( const node_ptr &state) const
    {
        leafs_list eles;

        static int k = 0, j = 0;

        ++k;
        ++j;

        if ( k >= 15 ) 
            return eles;
            

        for(int i = j; i < j+2; ++i)
            eles.push_back(makeNode(state->getState()+i, state));

        return eles;

    }

    bool isGoal (const int & value) const {
        return ( value == 104 );
    }
};


DefClassProblem(AlphabetProblem, char)
{
    AlphabetProblem()
    : Problem('A') 
    {
        auto &b = getRoot().connect1('B');
            auto &d = b.connect1('D');
                auto &h = d.connect1('H');
                auto &i = d.connect1('I');
            auto &e = b.connect1('E');
                auto &j = e.connect1('J');
                auto &k = e.connect1('K');

        auto &c = getRoot().connect1('C');
            auto &f = c.connect1('F');
                auto &l = f.connect1('L');
                auto &m = f.connect1('M');
            auto &g = c.connect1('G');
                auto &n = g.connect1('N');
                auto &o = g.connect1('O');
    }

    bool isGoal (const char & n) const 
    { return ( n == 'M' ); }

};

DefClassProblem(RomaniaCities, string)
{
    DefConstructorProblem(RomaniaCities, "Arad")
    {
        Node<string>::Maker maker;
        auto zerind     = maker("Zerind");
        auto oradea     = maker("Oradea");
        auto sibiu      = maker("Sibiu");
        auto fagaras    = maker("Fagaras");
        auto bucharest  = maker("Bucharest");
        auto rimincu    = maker("Rimnicu Vilcea");
        auto pitesi     = maker("Pitesti");
        auto giurgiu    = maker("Giurgiu");
        auto craiova    = maker("Craiova");
        auto drobeta    = maker("Drobeta");
        auto mehadia    = maker("Mehadia");
        auto lugoj      = maker("Lugoj");
        auto timisoara  = maker("Timisoara");
        auto urziceni   = maker("Urziceni");
        auto hirsova    = maker("Hirsova");
        auto valsui     = maker("Valsui");
        auto iasi       = maker("Iasi");
        auto neamt      = maker("Neamt");
        auto eforie     = maker("Eforie");

        Node<string>::Edge e;

        initial()->connect( e(zerind,75), e(sibiu, 140), e(timisoara, 118) );
        oradea->connect( e(zerind,71), e(sibiu,151) );
        sibiu->connect( e(fagaras,99), e(rimincu, 80) );
        rimincu->connect( e(pitesi, 97), e(craiova,146) );
        lugoj->connect( e(timisoara,111), e(mehadia,70) );
        drobeta->connect( e(mehadia,75), e(craiova,120) );
        pitesi->connect( e(craiova,138), e(bucharest,101) );
        bucharest->connect( e(fagaras,211), e(urziceni, 85), e(giurgiu,90));
        hirsova->connect(e(urziceni,98), e(eforie,86));
        valsui->connect( e(urziceni, 142), e(iasi,92));
        neamt->connect( e(iasi,87) );

        hTable.emplace(initial(), 366);
        hTable.emplace(bucharest, 0);
        hTable.emplace(craiova, 160);
        hTable.emplace(drobeta, 242);
        hTable.emplace(eforie, 161);
        hTable.emplace(fagaras, 176);
        hTable.emplace(giurgiu, 77);
        hTable.emplace(hirsova, 151);
        hTable.emplace(iasi, 226);
        hTable.emplace(lugoj, 244);
        hTable.emplace(mehadia, 241);
        hTable.emplace(neamt, 234);
        hTable.emplace(oradea, 380);
        hTable.emplace(pitesi, 100);
        hTable.emplace(rimincu, 193);
        hTable.emplace(sibiu, 253);
        hTable.emplace(timisoara, 329);
        hTable.emplace(urziceni, 80);
        hTable.emplace(valsui, 199);
        hTable.emplace(zerind, 374);
    }

    bool isGoal (const string &city) const 
    { return city == "Bucharest"; }

    long F(const node_ptr &n, const long &gn, const long &parent_cost) const 
    { return H(n) + gn; }

    long H(const node_ptr &n) const 
    { 
        return hTable.at(n);
    }

private:
    node_type::nodeptr_cost_map hTable;
};



typedef tuple<int, int, int> mcbVec;
DefClassProblem(MiCaBo, mcbVec)
{
    DefConstructorProblem(MiCaBo, mcbVec(3,3,1))
    { }

    leafs_list successors(const node_ptr &state) const
    { 
        leafs_list leafs;
        for( const auto &act : actions ) {
            const auto next = apply(state, act);
            if ( isValid(next) && isValid(otherSide(next)) )
                leafs.push_back(makeNode(next, state, H(next)));
        }

        return leafs;
    }

    bool checkLimit(const int &c) const 
    { 
        return ( c <= 3 && c >= 0 );
    }

    mcbVec otherSide(const mcbVec &succ) const
    {
        const int &ms = get<0>(succ);
        const int &cs = get<1>(succ);
        const int &b = get<2>(succ);

        return mcbVec(3-ms, 3-cs, 1-b);
    }

    bool isValid(const mcbVec &succ) const
    {
        const int &ms = get<0>(succ);
        const int &cs = get<1>(succ);
        const int &b = get<2>(succ);

        return checkLimit(ms) && checkLimit(cs) && ( ms == 0 ? true : ms >= cs ) && (b == 0 || b == 1);
    }

    long H(const node_ptr &node) const
    {
        const auto &state = node ->getState();
        return  H(state);
    }


    long H(const mcbVec &state) const
    {
        return  get<0>(state) + get<1>(state);
    }


    mcbVec apply(const node_ptr &node, const mcbVec &action) const
    {
        const auto &state = node->getState();
        return mcbVec( 
                get<0>(state) +  get<0>(action),
                get<1>(state) +  get<1>(action),
                get<2>(state) +  get<2>(action)
            );
    }

    bool isGoal (const mcbVec &state) const 
    { return state == mcbVec(0,0,0); }

    const vector<mcbVec> actions = {
        mcbVec(-1,-1,-1), mcbVec(-1,0,-1), mcbVec(0,-1,-1), mcbVec(-2,0,-1), mcbVec(0,-2,-1), 
        mcbVec(1,1,1), mcbVec(1,0,1), mcbVec(0,1,1), mcbVec(2,0,1), mcbVec(0,2,1),
    };
};



#endif
