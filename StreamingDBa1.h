// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "AvlTrees.h"

typedef struct movie_t *movie;
typedef struct user_t *user;
typedef struct group_t *Group;


void Auxdestructorgrouptree(Node<Group>* node);



class streaming_database {
private:
    Avl_tree<movie> *movie_tree;
    Avl_tree<user> *user_tree;
    Avl_tree<Group> *group_tree;
    Avl_tree<movie> *comedy_tree;
    Avl_tree<movie> *drama_tree;
    Avl_tree<movie> *action_tree;
    Avl_tree<movie> *fantasy_tree;
    int num_of_comedy;
    int num_of_drama;
    int num_of_action;
    int num_of_fantasy;

	
public:
	// <DO-NOT-MODIFY> {
	
	streaming_database();

	virtual ~streaming_database();
	
	StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);
	
	StatusType remove_movie(int movieId);
	
	StatusType add_user(int userId, bool isVip);
	
	StatusType remove_user(int userId);
	
	StatusType add_group(int groupId);
	
	StatusType remove_group(int groupId);

	StatusType add_user_to_group(int userId, int groupId);
	
	StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);
	
	output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);
	
	output_t<int> get_group_recommendation(int groupId);
	
	// } </DO-NOT-MODIFY>
};


#endif // STREAMINGDBA1_H_
