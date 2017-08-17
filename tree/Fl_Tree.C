#include <FL/Fl_Node.H>
#include <FL/Fl_Tree.H>
#include <stdlib.h> // qsort

Fl_Tree::Fl_Tree(int x,int y,int w,int h)
:Fl_Widget(x,y,w,h){
	first_=0;
	last_=0;
	top_=0;
	top_depth_=0;
	damaged_=0;
}
	
void Fl_Tree::draw_node(int depth,int cy,Fl_Node* node){
	fl_color(FL_BLACK);
	fl_rectf(x(),cy,depth*16,16);
	fl_color(FL_WHITE);
	fl_rectf(x()+depth*16,cy,w()-depth*16,16);
}

Fl_Node* Fl_Tree::find(int fy,int& depth,int& ry){
	int cy=parent()->y()+top_yoffset_;
	int ey=parent()->y()+parent()->h();
	depth=top_depth_;
	Fl_Node* node=top_;
	if (fy<cy) return 0;
	while (cy<ey && node){
		ry=cy;
		cy+=height(node);
		if (cy>fy) return node;
		if (node->sub_){
			node=node->sub_;
			depth++;
		}else if (node->next_){
			node=node->next_;
		}else{
			while (node && !node->next_){
				node=node->up_;
				depth--;
			}
			if (node) node=node->next_;
		}
	}
	return 0;
}

void Fl_Tree::update_height(void){
	resize(x(),y(),w(),total_height(first_));
}

#include <stdio.h>

void Fl_Tree::draw(void){
	update_top();
	int cy=parent()->y()+top_yoffset_;
	int ey=parent()->y()+parent()->h();
	int depth=top_depth_;
	Fl_Node* node=top_;
	bool drawing=false;
	//printf("DAMAGE %d %d %d\n",damage(),FL_DAMAGE_ALL,FL_DAMAGE_CHILD);
	if (damage()==FL_DAMAGE_ALL) drawing=true;
	if (damage()==FL_DAMAGE_CHILD && damaged_==0) drawing=true;
	while (cy<ey && node){
		if (damaged_==node){
			if (damage()==FL_DAMAGE_CHILD){
				draw_node(depth,cy,node);
				return;
			}
			drawing=true;
		}
		//printf("%s %d\n",(char*) node->data(),drawing);
		if (drawing) draw_node(depth,cy,node);
		cy+=height(node);
		if (node->sub_){
			//printf("has sub\n");
			node=node->sub_;
			depth++;
		}else if (node->next_){
			//printf("has no sub\n");
			node=node->next_;
		}else{
			while (node && !node->next_){
				node=node->up_;
				depth--;
			}
			if (node) node=node->next_;
		}
	}
	fl_color(parent()->color());
	fl_rectf(x(),cy,w(),ey-cy);
}

int (*s_node_compare_)(Fl_Node *, Fl_Node *)=0;

int s_compare_(void* a,void *b){
	Fl_Node* nodeA=*(Fl_Node**)a;
	Fl_Node* nodeB=*(Fl_Node**)b;
	return s_node_compare_(nodeA,nodeB);
}

Fl_Node*	Fl_Tree::sort_(
	Fl_Node* start,int (*compar)(Fl_Node *, Fl_Node *),
	bool down){
	int i;
	Fl_Node* node;
	
	i=0;
	node=start;
	while (node){
		node=node->next_;
		i++;
	}
	Fl_Node** array=new Fl_Node*[i];

	i=0;
	node=start;
	while (node){
		array[i]=node;
		node=node->next_;
		i++;
	}
	s_node_compare_=compar;
	qsort(array,i,sizeof(Fl_Node*),(int (*)(const void*,const void*))s_compare_);

	start=array[0];
	int j=1;
	node=start;
	while (j<i){
		node->next_=array[j];		
		node=node->next_;
		j++;
	}
	node->next_=0;
	
	if (down){
		node=start;
		while (node){
			if (node->sub_)
				node->sub_=sort_tree(node->sub_,compar);
			node=node->next_;
		}	
	}
	
	delete [] array;
	
	return start;
}

Fl_Node*	Fl_Tree::sort(Fl_Node* start,int (*compar)
	(Fl_Node *, Fl_Node*)){
	return sort_(start,compar,0);
}

Fl_Node*	Fl_Tree::sort_tree(Fl_Node* start,int (*compar)
	(Fl_Node *, Fl_Node*)){
	return sort_(start,compar,1);
}

void Fl_Tree::sort(int (*compar)(Fl_Node *, Fl_Node *)){
	first_=top_=sort(first_,compar);
}

void Fl_Tree::sort_tree(int (*compar)(Fl_Node *, Fl_Node *)){
	first_=top_=sort_tree(first_,compar);
}


void Fl_Tree::update_top(void){
	Fl_Node *node=first_;
	int py=parent()->y();
	int ly=y();
	int h=0;
	int depth=0;

	while (node && ly+(h=height(node))<=py){
		ly+=h;
		if (node->sub_){
			node=node->sub_;
			depth++;
		}else if (node->next_){
			node=node->next_;
		}else{
			while (node && !node->next_){
				node=node->up_;
				depth--;
			}
			if (node) node=node->next_;
		}
	}
	
	top_=node;
	top_depth_=depth;
	top_yoffset_=ly-py;
}

int  Fl_Tree::total_height(Fl_Node* node){
	int ret=0;
	int depth=1;
	while (node){
		ret+=height(node);
		if (node->sub_){
			node=node->sub_;
			depth++;
		}else if (node->next_){
			node=node->next_;
		}else{
			while (node && !node->next_){
				node=node->up_;
				depth--;
				if (depth<=0) node=0;
			}
			if (node) node=node->next_;
		}
	}
	return ret;
}


#include <stdlib.h>

int  Fl_Tree::height(Fl_Node* node){
	return 17;
}

int Fl_Tree::namesort(Fl_Node* a,Fl_Node* b){
	return strcmp((char*)a->data(),(char*) b->data());	
}

void Fl_Tree::sort_cb(Fl_Widget* w,void* ptr){
	Fl_Tree* t=(Fl_Tree*) ptr;
	t->sort_tree(namesort);
	t->redraw();
}

