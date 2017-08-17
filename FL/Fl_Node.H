#ifndef Fl_Node_H
#define Fl_Node_H

class Fl_Node {
friend class Fl_Tree;
friend class Fl_ToggleTree;
friend class Fl_TreeBuilder;
protected:
	Fl_Node*	prev_;
	Fl_Node*	next_;
	Fl_Node*	sub_;
	Fl_Node*	up_;
	void*		data_;
public:
	Fl_Node(){
		prev_=0;
		next_=0;
		sub_=0;
		up_=0;
		data_=0;
	}
	void* data(void){ return data_; }
	void data(void* ptr){ data_=ptr; }
	void sub(Fl_Node* s){ sub_=s; }
};

#endif
