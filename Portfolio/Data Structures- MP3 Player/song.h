/* @Author
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date: 23.11.2016 */

#define SNAME_LENGTH 50
#define LNAME_LENGTH 50
#define STYLE_LENGTH 30
#define SINGER_LENGTH 50

struct song;
struct playlist;
struct song_node;

struct song {
	char *name = new char[SNAME_LENGTH];
	char *singer = new char[SINGER_LENGTH];
	char *style = new char[STYLE_LENGTH];
	int year;
};

struct playlist {
	int songnumber;
	char *name = new char[LNAME_LENGTH];
	song_node* head;
	playlist *next;
	playlist *prev;
};

struct song_node {
	playlist *parent;
	song *data;
	song_node *next;
	song_node *prev;

};

