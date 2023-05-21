// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
// 

#include "StreamingDBa1.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void query_get_all_movies(string cmd, streaming_database *obj, Genre genre);

int main()
{

    int d1, d2, d3, g1;
    string b1;
    bool b;

    // Init
    streaming_database *obj = new streaming_database();

    // Execute all commands in file
    string op;
    while (cin >> op)
    {
        if (!op.compare("add_movie")) {
            cin >> d1 >> g1 >> d2 >> b1;
            if (!b1.compare("True")) {
                b = true;
            }
            else if (!b1.compare("False")) {
                b = false;
            }
            else {
                cout << "Invalid input format" << endl;
                return -1;
            }
            print(op, obj->add_movie(d1, (Genre) g1, d2, b));
        } else if (!op.compare("remove_movie")) {
            cin >> d1;
            print(op, obj->remove_movie(d1));
        } else if (!op.compare("add_user")) {
            cin >> d1 >> b1;
            if (!b1.compare("True")) {
                b = true;
            }
            else if (!b1.compare("False")) {
                b = false;
            }
            else {
                cout << "Invalid input format" << endl;
                return -1;
            }
            print(op, obj->add_user(d1, b));
        } else if (!op.compare("remove_user")) {
            cin >> d1;
            print(op, obj->remove_user(d1));
        } else if (!op.compare("add_group")) {
            cin >> d1;
            print(op, obj->add_group(d1));
        } else if (!op.compare("remove_group")) {
            cin >> d1;
            print(op, obj->remove_group(d1));
        } else if (!op.compare("add_user_to_group")) {
            cin >> d1 >> d2;
            print(op, obj->add_user_to_group(d1, d2));
        } else if (!op.compare("get_all_movies_count")) {
            cin >> g1;
            print(op, obj->get_all_movies_count((Genre) g1));
        } else if (!op.compare("get_all_movies")) {
            cin >> g1;
            query_get_all_movies(op, obj, (Genre) g1);
        } else if (!op.compare("user_watch")) {
            cin >> d1 >> d2;
            print(op, obj->user_watch(d1, d2));
        } else if (!op.compare("group_watch")) {
            cin >> d1 >> d2;
            print(op, obj->group_watch(d1, d2));
        } else if (!op.compare("get_num_views")) {
            cin >> d1 >> g1;
            print(op, obj->get_num_views(d1, (Genre) g1));
        } else if (!op.compare("rate_movie")) {
            cin >> d1 >> d2 >> d3;
            print(op, obj->rate_movie(d1, d2, d3));
        } else if (!op.compare("get_group_recommendation")) {
            cin >> d1;
            print(op, obj->get_group_recommendation(d1));
        } else {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit 
    delete obj;
    return 0;
}

// Helpers
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_movies(string cmd, streaming_database *obj, Genre genre)
{
    output_t<int> count = obj->get_all_movies_count(genre);
    int to_alloc = count.ans();
    if (to_alloc == 0)
    {
        //if there are no movies we will allocate 1 so that we will get failure instead of invalid input
        ++to_alloc;
    }
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS)
    {
        out_mem = new int[to_alloc];
        for (int i = 0; i < to_alloc; ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_movies(genre, out_mem);
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < to_alloc; ++i)
        {
            cout << out_mem[i] << endl;
        }
    }
    delete[] out_mem;
}

/*
#include <iostream>
#include "StreamingDBa1.h"

void my_query_get_all_movies(streaming_database *obj, Genre genre);
void test();

void my_query_get_all_movies(streaming_database *obj, Genre genre)
{
    output_t<int> count = obj->get_all_movies_count(genre);
    int to_alloc = count.ans();
    if (to_alloc == 0)
    {
        //if there are no movies we will allocate 1 so that we will get failure instead of invalid input
        ++to_alloc;
    }
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS)
    {
        out_mem = new int[to_alloc];
        for (int i = 0; i < to_alloc; ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_movies(genre, out_mem);
//    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < to_alloc; ++i)
        {
            std::cout << out_mem[i] << std::endl;
        }
    }
    delete[] out_mem;
}


void test() {
    streaming_database *obj = new streaming_database();

    obj->add_user_to_group(29076, 3836);
    obj->add_group(26348);
    obj->add_group(5304);
    obj->remove_movie(34152);
    obj->rate_movie(34212, 37408, 86);
    obj->user_watch(48722, 20888);
    obj->get_num_views(24991, static_cast<Genre>(1));
    obj->add_group(26143);
    obj->user_watch(48464, 9959);
    obj->add_group(25771);
    obj->add_movie(22189, static_cast<Genre>(1), 16, false);
    my_query_get_all_movies(obj, static_cast<Genre>(4));
//    obj->get_all_movies(static_cast<Genre>(4));
    obj->add_group(32937);
    obj->add_user_to_group(27526, 32937);
    obj->group_watch(37423, 22189);
    obj->add_user(5257, false);
    obj->get_all_movies_count(static_cast<Genre>(3));
    obj->get_group_recommendation(46742);
    obj->remove_movie(22189);
    obj->add_group(49);
    obj->get_all_movies_count(static_cast<Genre>(0));
    obj->get_all_movies_count(static_cast<Genre>(1));
    obj->remove_user(5257);
    obj->add_group(37800);
    obj->get_num_views(25951, static_cast<Genre>(1));
    obj->get_all_movies_count(static_cast<Genre>(3));
    obj->add_user(44579, false);
    obj->get_group_recommendation(17870);
    obj->add_user_to_group(44579, 26143);
    obj->remove_group(25771);
    obj->group_watch(26143, 17562);
    obj->remove_group(49);
    obj->add_user_to_group(3634, 5304);
    obj->add_movie(40343, static_cast<Genre>(1), 7, true);
    obj->get_all_movies_count(static_cast<Genre>(2));
    obj->add_group(10170);
    obj->add_movie(39489, static_cast<Genre>(3), 1, true);
    obj->group_watch(26143, 37719);
    obj->add_group(37099);
    obj->add_movie(44059, static_cast<Genre>(3), 9, false);
    obj->get_group_recommendation(26143);
    obj->group_watch(26143, 44059);
    obj->remove_movie(40343);
    obj->user_watch(44579, 44059);
    obj->user_watch(44579, 44059);
    obj->add_movie(17167, static_cast<Genre>(0), 11, true);
    obj->add_group(38192);
    obj->add_user_to_group(10247, 38192);
    obj->user_watch(44579, 44059);
    obj->get_all_movies_count(static_cast<Genre>(4));
    obj->add_user(448, false);
    obj->group_watch(26143, 44059);
    obj->add_user(41050, true);
    obj->add_group(41587);
    my_query_get_all_movies(obj, static_cast<Genre>(3));
//    obj->get_all_movies(3);
    obj->group_watch(26143, 44059);
    obj->add_movie(23159, static_cast<Genre>(2), 4, true);
    obj->user_watch(41050, 44059);
    obj->add_user_to_group(41050, 32937);
    obj->remove_movie(39489);
    obj->get_num_views(41050, static_cast<Genre>(4));
    obj->add_group(46171);
    obj->user_watch(41050, 23159);
    obj->get_num_views(41050, static_cast<Genre>(2));
    obj->user_watch(41050, 17167);
    obj->user_watch(41050, 23159);
    obj->group_watch(32937, 44059);
    obj->user_watch(44579, 44059);
    obj->group_watch(32937, 23159);
    obj->remove_group(32937);
    obj->add_movie(19652, static_cast<Genre>(4), 5, false);
    obj->add_group(4786);
    obj->remove_group(26348);
    obj->get_group_recommendation(26143);
    obj->get_group_recommendation(26143);
    obj->user_watch(448, 44059);
    my_query_get_all_movies(obj, static_cast<Genre>(1));
//    obj->get_all_movies(static_cast<Genre>(1));
    obj->add_movie(29318, static_cast<Genre>(3), 19, false);
    obj->user_watch(41050, 29318);
    obj->add_movie(29281, static_cast<Genre>(2), 3, true);
    obj->user_watch(41050, 29318);
    my_query_get_all_movies(obj, static_cast<Genre>(1));
    my_query_get_all_movies(obj, static_cast<Genre>(0));
//    obj->get_all_movies(1);
//    obj->get_all_movies(0);
    obj->add_user_to_group(41050, 38192);
    obj->get_all_movies_count(static_cast<Genre>(2));
    obj->get_all_movies_count(static_cast<Genre>(3));
    obj->add_movie(2772, static_cast<Genre>(0), 14, false);
    obj->add_user_to_group(448, 38192);
    my_query_get_all_movies(obj, static_cast<Genre>(0));
    my_query_get_all_movies(obj, static_cast<Genre>(2));
//    obj->get_all_movies(0);
//    obj->get_all_movies(2);
    obj->add_user_to_group(11753, 37099);
    obj->get_group_recommendation(26143);
    obj->remove_movie(44059);
    obj->remove_user(448);
    my_query_get_all_movies(obj, static_cast<Genre>(1));
//    obj->get_all_movies(1);
    obj->get_all_movies_count(static_cast<Genre>(2));
    obj->remove_group(10170);
    obj->remove_group(46171);
    obj->get_num_views(44579, static_cast<Genre>(3));
    obj->add_user_to_group(42147, 37099);
    obj->get_all_movies_count(static_cast<Genre>(0));
    obj->add_movie(35004, static_cast<Genre>(3), 20, true);
    obj->add_group(30729);
    obj->add_group(35460);
    obj->get_all_movies_count(static_cast<Genre>(2));
    my_query_get_all_movies(obj, static_cast<Genre>(0));
//    obj->get_all_movies(0);
    obj->group_watch(38192, 29318);
    obj->user_watch(41050, 29318);
    obj->user_watch(44579, 2772);
    obj->get_all_movies_count(static_cast<Genre>(0));
    obj->get_group_recommendation(26143);
    obj->add_user_to_group(9673, 37099);
    obj->user_watch(44579, 2772);
    obj->add_movie(6653, static_cast<Genre>(1), 12, true);
    obj->group_watch(38192, 35004);
    obj->add_group(3176);
    obj->add_user_to_group(2278, 41587);
    obj->group_watch(38192, 35004);
    obj->user_watch(41050, 17167);
    obj->get_num_views(41050, static_cast<Genre>(0));
    obj->user_watch(44579, 29318);
    obj->group_watch(26143, 2772);
    obj->remove_group(26143);
    obj->add_user_to_group(44579, 35460);
    my_query_get_all_movies(obj, static_cast<Genre>(3));
//    obj->get_all_movies(3);
    obj->add_movie(23161, static_cast<Genre>(4), 19, true);
    obj->add_user_to_group(1404, 4786);
    obj->add_user_to_group(45872, 37800);
    obj->get_group_recommendation(38192);
    obj->add_user(32741, false);
    obj->remove_movie(23159);
    obj->add_group(6530);
    obj->rate_movie(44579, 29318, 17);
    my_query_get_all_movies(obj, static_cast<Genre>(3));
//    obj->get_all_movies(3);
    obj->rate_movie(44579, 2772, 35);
    obj->remove_movie(2772);
    obj->user_watch(44579, 29318);
    obj->remove_user(32741);
    obj->add_user(20129, true);
    obj->group_watch(38192, 29318);
    obj->remove_group(3176);
    obj->get_group_recommendation(35460);
    obj->add_user_to_group(20129, 41587);
    obj->user_watch(44579, 29318);
    obj->user_watch(44579, 29318);
    my_query_get_all_movies(obj, static_cast<Genre>(0));
//    obj->get_all_movies(0);
    obj->user_watch(44579, 29318);
    obj->get_group_recommendation(35460);
    obj->remove_user(20129);
    obj->add_group(21233);
    obj->remove_group(37099);
    obj->get_num_views(41050, static_cast<Genre>(3));
    obj->add_user(46636, true);
    obj->add_group(16278);
    std::cout << "---------------------------" << std::endl;
    my_query_get_all_movies(obj, static_cast<Genre>(4));
//    obj->get_all_movies(4);
    std::cout << "---------------------------" << std::endl;
    obj->get_num_views(46636, static_cast<Genre>(2));
    obj->remove_group(16278);
    obj->add_user_to_group(46636, 37800);
    obj->group_watch(38192, 6653);
    obj->get_group_recommendation(38192);
    obj->remove_user(44579);
    obj->add_group(5417);
    obj->get_group_recommendation(38192);
    obj->remove_group(37800);
    obj->add_movie(26386, static_cast<Genre>(1), 13, false);
    obj->user_watch(41050, 29318);
    obj->user_watch(32023, 29318);
    obj->get_all_movies_count(static_cast<Genre>(2));
    obj->add_user_to_group(46636, 5417);
    obj->remove_user(46636);
    obj->remove_user(41050);
    obj->rate_movie(48046, 26386, 56);
    obj->add_user_to_group(7296, 5304);
    my_query_get_all_movies(obj, static_cast<Genre>(1));
//    obj->get_all_movies(1);
    obj->add_group(12746);
    obj->add_user_to_group(37719, 5417);
    obj->get_group_recommendation(32038);
    obj->add_movie(23904, static_cast<Genre>(0), 18, true);
    obj->add_user(47461, false);
    my_query_get_all_movies(obj, static_cast<Genre>(0));
//    obj->get_all_movies(0);
    obj->add_group(29018);
    obj->get_num_views(47461, static_cast<Genre>(1));
    my_query_get_all_movies(obj, static_cast<Genre>(1));
//    obj->get_all_movies(1);
    obj->user_watch(18730, 23904);
    my_query_get_all_movies(obj, static_cast<Genre>(0));
//    obj->get_all_movies(0);
    obj->add_user_to_group(47461, 12746);
    obj->add_user(28012, true);
    obj->add_user_to_group(28012, 5304);
    obj->add_user(10393, false);
    obj->get_group_recommendation(5304);
    obj->group_watch(12746, 26386);
    obj->get_group_recommendation(5304);
    obj->get_group_recommendation(5304);
    obj->add_movie(27654, static_cast<Genre>(1), 12, true);
    obj->remove_movie(27654);
    obj->group_watch(12746, 29318);
    obj->add_user(3579, true);
    obj->get_all_movies_count(static_cast<Genre>(0));
    obj->remove_user(10393);
    obj->rate_movie(28012, 29318, 88);

    delete obj;

}

int main() {
    test();
    return 0;
}
*/