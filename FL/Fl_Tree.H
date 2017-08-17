#ifndef Fl_Tree_H
#define Fl_Tree_H

#include <FL/Fl_Node.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Scroll.H>

#define FL_DAMAGE_TREE 0x40

class Fl_TreeBuilder {
Fl_Node* first_;
Fl_Node* current_;
public:
	Fl_TreeBuilder(Fl_Node* start){
		first_=start;
		current_=start;
	}
	void next(Fl_Node* node){
		current_->next_=node;
		node->prev_=current_;
		node->up_=current_->up_;
		current_=node;
	}
	void sub(Fl_Node* node){
		current_->sub_=node;
		node->up_=current_;
		current_=node;
	}
	void up(void){
		current_=current_->up_;
	}
        void set(Fl_Node* node){
                current_=node;
        } 
        Fl_Node* get(void){
                return current_;
        }
};


class Fl_Tree:public Fl_Widget {
protected:
	Fl_Node*	first_;
	Fl_Node*	last_;
	Fl_Node*	top_;
	int top_depth_;
	int top_yoffset_;
public:
	Fl_Tree(int x,int y,int w,int h);
	void start(Fl_Node* n){
		first_=n;
	}
	Fl_Node* start(void){
		return first_;
	}
	virtual void draw(void);
	void update_height(void);
protected:
	Fl_Node*	damaged_;
	
	virtual int  height(Fl_Node* node);
	int  total_height(Fl_Node* node);
	Fl_Node* find(int fy,int& depth,int& ry);
	void update_top(void);
	virtual void draw_node(int depth,int cy,Fl_Node* node);
	virtual int handle(int event){ return 1; }

	Fl_Node*	sort_(	Fl_Node* start,
						int (*compar)(Fl_Node *, Fl_Node *),
						bool down);
public:
	Fl_Node*	sort(Fl_Node* start,int (*compar)(Fl_Node *, Fl_Node *));
	Fl_Node*	sort_tree(Fl_Node* start,int (*compar)(Fl_Node *, Fl_Node *));

	void sort(int (*compar)(Fl_Node *, Fl_Node *));
	void sort_tree(int (*compar)(Fl_Node *, Fl_Node *));

	static int namesort(Fl_Node* a,Fl_Node* b);
	static void sort_cb(Fl_Widget* w,void* ptr);
};

#endif
