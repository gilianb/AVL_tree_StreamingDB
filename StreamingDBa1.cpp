#include "StreamingDBa1.h"


struct movie_t{
    int movieID=0;
    int views=0;
    int rate=0;
    bool vipOnly=false;
    Genre genre=Genre::NONE;

};

struct user_t{
    int num_of_film_viewed=0;
    int userID=0;
    group group= nullptr;
    bool vip= false;
    int nfantasy=0;
    int ncomedy=0;
    int naction=0;
    int nfiction=0;

};

struct group_t{
    int groupID=0;
    bool vip= false;
    int numberOfUser=0;
    int num_of_film_viewed=0;
    Avl_tree<user> *usergroup_tree= nullptr;
    int Nfantasy=0;
    int Ncomedy=0;
    int Naction=0;
    int Nfiction=0;
    int WTfantasy=0;
    int WTaction=0;
    int WTfiction=0;
    int WTcomedy=0;
};


streaming_database::streaming_database()
{
    try {
        movie_tree = new Avl_tree<movie>;
    }
    catch (std::bad_alloc &) {
        throw ;
    }
    try {
        user_tree = new Avl_tree<user>;
    }
    catch (std::bad_alloc &) {
        delete movie_tree;
        throw ;
    }
    try {
        group_tree = new Avl_tree<group>;
    }
    catch (std::bad_alloc &) {
        delete user_tree;
        delete movie_tree;
        throw ;
    }
    try {
        action_tree = new Avl_tree<movie>;
    }
    catch (std::bad_alloc &) {
        delete user_tree;
        delete movie_tree;
        delete group_tree;
        throw ;
    }
    try {
        fantasy_tree = new Avl_tree<movie>;
    }
    catch (std::bad_alloc &) {
        delete user_tree;
        delete movie_tree;
        delete group_tree;
        delete action_tree;
        throw ;
    }
    try {
        drama_tree = new Avl_tree<movie>;
    }
    catch (std::bad_alloc &) {
        delete user_tree;
        delete movie_tree;
        delete group_tree;
        delete action_tree;
        delete fantasy_tree;
        throw ;
    }
    try {
        comedy_tree = new Avl_tree<movie>;
    }
    catch (std::bad_alloc &) {
        delete user_tree;
        delete movie_tree;
        delete group_tree;
        delete action_tree;
        delete fantasy_tree;
        delete drama_tree;
        throw ;
    }

    num_of_action=0;
    num_of_comedy=0;
    num_of_drama=0;
    num_of_fantasy=0;
}

streaming_database::~streaming_database()
{
    //aux destructor pour tout le monde
    delete user_tree;
    delete movie_tree;
    delete group_tree;
    delete action_tree;
    delete fantasy_tree;
    delete drama_tree;
    delete comedy_tree;
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(views<0 || genre==Genre::NONE ||movieId<=0){
        return StatusType::INVALID_INPUT;
    }//invalid input check

    if(movie_tree->FindNode(movie_tree->GetRoot(),movieId)!= nullptr){
        return StatusType::FAILURE;
    }//this movie already exist

    movie movie_to_add= nullptr;

    try {
        movie_to_add= new movie_t;
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }

    movie_to_add->genre=genre;
    movie_to_add->movieID=movieId;
    movie_to_add->views=views;
    movie_to_add->vipOnly=vipOnly;

    Node<movie> *new_movie = nullptr;

    try {
        new_movie = new Node<movie>;
    }
    catch (std::bad_alloc &) {
        delete movie_to_add;
        return StatusType::ALLOCATION_ERROR;
    }

    new_movie->SetKey(movieId);
    new_movie->SetElement(movie_to_add);
    new_movie->SetHeight(0);
    new_movie->SetFatherNode(nullptr);
    new_movie->SetNodeLeft(nullptr);
    new_movie->SetNodeRight(nullptr);

    movie_tree->InsertNode(new_movie);
    if (genre==Genre::DRAMA){
        drama_tree->InsertNodeInGenre(new_movie);
        num_of_drama++;
    }
    else if(genre==Genre::ACTION){
        action_tree->InsertNodeInGenre(new_movie);
        num_of_action++;
    }
    else if (genre==Genre::COMEDY){
        comedy_tree->InsertNodeInGenre(new_movie);
        num_of_comedy++;
    }
    else if (genre==Genre::FANTASY){
        fantasy_tree->InsertNodeInGenre(new_movie);
        num_of_fantasy++;
    }

	return StatusType::SUCCESS;
}




StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId<=0){
        return StatusType::INVALID_INPUT;
    }//input is invalid

    if(movie_tree->FindNode(movie_tree->GetRoot(),movieId)== nullptr){
        return StatusType::FAILURE;
    }//this movie doesn't exist


    Node<movie> *temp_node = movie_tree->FindNode(movie_tree->GetRoot(),movieId);
    int view = temp_node->GetElement()->views;
    int rate = temp_node->GetElement()->rate;
    Genre genre=temp_node->GetElement()->genre;

    movie_tree->RemoveNode(movieId);//remove from movie tree


    //remove from genre tree
    if (genre==Genre::DRAMA){
        temp_node=drama_tree->FindNodeInGenre(drama_tree->GetRoot(),movieId,rate,view);
        drama_tree->RemoveNode(temp_node);
        num_of_drama--;
    }
    else if(genre==Genre::ACTION){
        temp_node=action_tree->FindNodeInGenre(action_tree->GetRoot(),movieId,rate,view);
        action_tree->RemoveNode(temp_node);
        num_of_action--;
    }
    else if (genre==Genre::COMEDY){
        temp_node=comedy_tree->FindNodeInGenre(comedy_tree->GetRoot(),movieId,rate,view);
        comedy_tree->RemoveNode(temp_node);
        num_of_comedy--;
    }
    else if (genre==Genre::FANTASY){
        temp_node=fantasy_tree->FindNodeInGenre(fantasy_tree->GetRoot(),movieId,rate,view);
        fantasy_tree->RemoveNode(temp_node);
        num_of_fantasy--;
    }

	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId<=0){
        return StatusType::INVALID_INPUT;
    }

    if(user_tree->FindNode(user_tree->GetRoot(),userId)!= nullptr){
        return StatusType::FAILURE;
    }//this user already exist

    user newUser= nullptr;
    try {
        newUser= new user_t;
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }

    newUser->userID=userId;
    newUser->vip=isVip;

    Node<user> *user_to_add = nullptr;
    try {
        user_to_add= new Node<user>;
    }
    catch (std::bad_alloc &) {
        delete newUser;
        return StatusType::ALLOCATION_ERROR;
    }
    user_to_add->SetKey(userId);
    user_to_add->SetElement(newUser);
    user_to_add->SetHeight(0);
    user_to_add->SetFatherNode(nullptr);
    user_to_add->SetNodeLeft(nullptr);
    user_to_add->SetNodeRight(nullptr);

    user_tree->InsertNode(user_to_add);


	return StatusType::SUCCESS;
}



StatusType streaming_database::remove_user(int userId)
{
    if(userId<=0){
        return StatusType::INVALID_INPUT;
    }

    if(user_tree->FindNode(user_tree->GetRoot(),userId)== nullptr){
        return StatusType::FAILURE;
    }//this user doesn't exist

    Node<user>* user_to_remove= user_tree->FindNode(user_tree->GetRoot(),userId);

    if(user_to_remove->GetElement()->group!= nullptr) {
        group group1 = user_to_remove->GetElement()->group;
        user user1= user_to_remove->GetElement();

        user1->naction += group1->WTaction;
        user1->ncomedy += group1->WTcomedy;
        user1->nfantasy += group1->WTfantasy;
        user1->nfiction += group1->WTfiction;

        group1->Naction -= user1->naction;
        group1->Ncomedy -= user1->ncomedy;
        group1->Nfantasy -= user1->nfantasy;
        group1->Nfiction -= user1->nfiction;

        group1->usergroup_tree->RemoveNode(userId);
        group1->numberOfUser--;

    }
    user_tree->RemoveNode(userId);

	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId<=0){
        return StatusType::INVALID_INPUT;
    }

    if(group_tree->FindNode(group_tree->GetRoot(),groupId)!= nullptr){
        return StatusType::FAILURE;
    }//this group already exist

    group new_group= nullptr;
    try {
        new_group= new group_t;
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }

    new_group-> groupID=groupId;
    new_group-> usergroup_tree=new Avl_tree<user>;

    Node<group> *group_to_add = nullptr;
    try {
        group_to_add= new Node<group>;
    }
    catch (std::bad_alloc &) {
        delete new_group;
        return StatusType::ALLOCATION_ERROR;
    }

    group_to_add->SetKey(groupId);
    group_to_add->SetElement(new_group);
    group_to_add->SetHeight(0);
    group_to_add->SetFatherNode(nullptr);
    group_to_add->SetNodeLeft(nullptr);
    group_to_add->SetNodeRight(nullptr);

    group_tree->InsertNode(group_to_add);

	return StatusType::SUCCESS;
}

void passingOnTheTree(Node<user> *node, group group1) {
    if ( node == nullptr) {
        return;
    }
    passingOnTheTree(node->GetNodeLeft());
    passingOnTheTree(node->GetNodeRight());
    node->GetElement()->group= nullptr;
    user user1=node->GetElement();

    user1->naction += group1->WTaction;
    user1->ncomedy += group1->WTcomedy;
    user1->nfantasy += group1->WTfantasy;
    user1->nfiction += group1->WTfiction;
}

StatusType streaming_database::remove_group(int groupId)
{

    if(groupId<=0){
        return StatusType::INVALID_INPUT;
    }

    if(group_tree->FindNode(group_tree->GetRoot(),groupId)== nullptr){
        return StatusType::FAILURE;
    }//this group doesn't exist

    Node<group> *group_to_remove = group_tree->FindNode(group_tree->GetRoot(),groupId);
    group group1=group_to_remove->GetElement();

    //fix group pointer and ngenre in user
    passingOnTheTree(group1->usergroup_tree->GetRoot(),group1);

    group1->usergroup_tree->AuxDistructorTree( group1->usergroup_tree->GetRoot());
    group_tree->RemoveNode(groupId);


	return StatusType::SUCCESS;
}


StatusType streaming_database::add_user_to_group(int userId, int groupId)
{

    if(groupId<=0 || userId<=0){
        return StatusType::INVALID_INPUT;
    }

    if(group_tree->FindNode(group_tree->GetRoot(),groupId)== nullptr){
        return StatusType::FAILURE;
    }//this group dosent exist

    if(user_tree->FindNode(user_tree->GetRoot(),userId)== nullptr){
        return StatusType::FAILURE;
    }//this user dosent exist

    Node<user> *user_to_add = user_tree->FindNode(user_tree->GetRoot(),userId);
    user user1=user_to_add->GetElement();

    if(user1->group!= nullptr){
        return StatusType::FAILURE;
    }//the user is already in a group

    Node<group> *group_to_add_in = group_tree->FindNode(group_tree->GetRoot(),groupId);
    group group1=group_to_add_in->GetElement();

    group1->usergroup_tree->InsertNode(user_to_add);
    if (user1->vip && !group1->vip){
        group1->vip=true;
    }

    //update group and user fields
    group1->numberOfUser++;
    user1->group=group1;

    group1->Naction += user1->naction;
    group1->Ncomedy += user1->ncomedy;
    group1->Nfantasy += user1->nfantasy;
    group1->Nfiction += user1->nfiction;

    user1->naction -= group1->WTaction;
    user1->ncomedy -= group1->WTcomedy;
    user1->nfantasy -= group1->WTfantasy;
    user1->nfiction -= group1->WTfiction;

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(movieId<=0 || userId<=0){
        return StatusType::INVALID_INPUT;
    }

    if(movie_tree->FindNode(movie_tree->GetRoot(),movieId)== nullptr){
        return StatusType::FAILURE;
    }//this movie dosent exist

    if(user_tree->FindNode(user_tree->GetRoot(),userId)== nullptr){
        return StatusType::FAILURE;
    }//this user dosent exist

    Node<user> *user_to_add = user_tree->FindNode(user_tree->GetRoot(),userId);
    user user1=user_to_add->GetElement();

    Node<movie> *movie_to_watch = movie_tree->FindNode(movie_tree->GetRoot(),movieId);
    movie movie1=movie_to_watch->GetElement();

    if( movie1->vipOnly && !user1->vip){
        return StatusType::FAILURE;
    }

    Genre genre_of_the_film=movie1->genre;
    group group1=user1->group;

    if (genre_of_the_film==Genre::DRAMA){
        user1->nfiction++;
        group1->Nfiction++;
    }
    else if(genre_of_the_film==Genre::ACTION){
        user1->naction++;
        group1->Naction++;
    }
    else if (genre_of_the_film==Genre::COMEDY){
        user1->ncomedy++;
        group1->Ncomedy++;
    }
    else if (genre_of_the_film==Genre::FANTASY){
        user1->nfantasy++;
        group1->Nfantasy++;
    }

    //movie_to_watch->Setkey2()
    movie1->views++;
    // TODO: update ets genre with new view

    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(movieId<=0 || groupId<=0){
        return StatusType::INVALID_INPUT;
    }

    if(movie_tree->FindNode(movie_tree->GetRoot(),movieId)== nullptr){
        return StatusType::FAILURE;
    }//this movie dosent exist

    if(group_tree->FindNode(group_tree->GetRoot(),groupId)== nullptr){
        return StatusType::FAILURE;
    }//this group dosent exist

    Node<movie> *movie_to_watch = movie_tree->FindNode(movie_tree->GetRoot(),movieId);
    movie movie1=movie_to_watch->GetElement();

    Node<group> *group_watch = group_tree->FindNode(group_tree->GetRoot(),groupId);
    group group1=group_watch->GetElement();

    if (group1->numberOfUser==0){
        return StatusType::FAILURE;
    }

    if( movie1->vipOnly && !group1->vip){
        return StatusType::FAILURE;
    }

    Genre genre_of_the_film=movie1->genre;

    if (genre_of_the_film==Genre::DRAMA){
        group1->WTfiction++;
        group1->Nfiction += group1->numberOfUser;
    }
    else if(genre_of_the_film==Genre::ACTION){
        group1->WTaction++;
        group1->Naction += group1->numberOfUser;
    }
    else if (genre_of_the_film==Genre::COMEDY){
        group1->WTcomedy++;
        group1->Ncomedy += group1->numberOfUser;
    }
    else if (genre_of_the_film==Genre::FANTASY){
        group1->WTfantasy++;
        group1->Nfantasy += group1->numberOfUser;
    }

    movie1->views += group1->numberOfUser;

	// TODO: update ets genre with new view


	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    // TODO: Your code goes here
    int get_count=0;
    if (genre==Genre::DRAMA){
        get_count = num_of_drama;
    }
    else if(genre==Genre::ACTION){
        get_count =num_of_action;
    }
    else if (genre==Genre::COMEDY){
        get_count=num_of_comedy;
    }
    else if (genre==Genre::FANTASY){
       get_count=num_of_fantasy;
    }
    else{
        get_count=num_of_fantasy+num_of_comedy+num_of_action+num_of_drama;
    }

    return  get_count;

}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    if(output== nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(num_of_fantasy+num_of_comedy+num_of_action+num_of_drama==0){
        return StatusType::FAILURE;
    }

    int* get_in_order;
    if (genre != Genre::NONE) {
        if (genre == Genre::DRAMA && num_of_drama == 0) {
            return StatusType::FAILURE;
            drama_tree->In
        }
        else if (genre == Genre::ACTION && num_of_action == 0) {
            return StatusType::FAILURE;
        }
        else if (genre == Genre::COMEDY && num_of_comedy == 0) {
            return StatusType::FAILURE;
        }
        else if (genre == Genre::FANTASY && num_of_fantasy == 0) {
            return StatusType::FAILURE;
        }
    }


    //output[0] = 4001;
    //output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}


