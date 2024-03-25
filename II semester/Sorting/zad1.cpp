#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Post {
    int friendId;
    int popularity;
    string content;
};

bool comparePosts(const Post& post1, const Post& post2) {
    return post1.popularity > post2.popularity;
}

std::vector<Post> sortPosts(const vector<Post>& posts, const vector<int>& selectedFriends) {
    vector<Post> selectedPosts;
    vector<Post> otherPosts;

    for (const auto& post : posts) {
        if (std::find(selectedFriends.begin(), selectedFriends.end(), post.friendId) != selectedFriends.end()) {
            selectedPosts.push_back(post);
        }
        else {
            otherPosts.push_back(post);
        }
    }

    sort(selectedPosts.begin(), selectedPosts.end(), comparePosts);
    sort(otherPosts.begin(), otherPosts.end(), comparePosts);

    selectedPosts.insert(selectedPosts.end(), otherPosts.begin(), otherPosts.end());
    return selectedPosts;
}

int main() {
    vector<Post> posts = {
        {1, 10, "Post 1"},
        {2, 5, "Post 2"},
        {3, 8, "Post 3"},
        {4, 6, "Post 4"},
        {5, 9, "Post 5"}
    };

    vector<int> selectedFriends = { 2, 4 }; //Wybrani znajomi w tym przypadku 2 i 4

    vector<Post> sortedPosts = sortPosts(posts, selectedFriends);

    cout << "Sorted Posts:" << std::endl;
    for (const auto& post : sortedPosts) {
        cout << "ID znajomego: " << post.friendId << ", Popularnosc: " << post.popularity << ", Zawartosc: " << post.content << std::endl;
    }

    return 0;
}
