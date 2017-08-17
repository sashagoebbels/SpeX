#include <FL/Fl_ToggleNode.H>
#include <FL/Fl_ToggleTree.H>
#include <FL/Fl.H>

#include <FL/open_icon.xpm>
#include <FL/closed_icon.xpm>

Fl_Pixmap* Fl_ToggleTree::sOpenIcon		=	new Fl_Pixmap(open_icon);
Fl_Pixmap* Fl_ToggleTree::sClosedIcon	=	new Fl_Pixmap(closed_icon);

void Fl_ToggleTree::selectrange(Fl_ToggleNode* start,Fl_ToggleNode* end,bool add){
	Fl_Node *node=first_;
	bool selecting=false;

	while (node){
		if (node==start || node==end){
			if (((Fl_ToggleNode*)node)->selected_==false){
				((Fl_ToggleNode*)node)->selected_=true;
				((Fl_ToggleNode*)node)->changed_=true;
			}
			if (start!=end) selecting=!selecting;
		}else{
			if (selecting){
				if (((Fl_ToggleNode*)node)->selected_==false){
					((Fl_ToggleNode*)node)->selected_=true;
					((Fl_ToggleNode*)node)->changed_=true;
				}
			}else{
				bool tmp=((Fl_ToggleNode*)node)->selected_;
				((Fl_ToggleNode*)node)->selected_&=add;
				((Fl_ToggleNode*)node)->changed_=tmp!=((Fl_ToggleNode*)node)->selected_;
			}
		}
		if (node->sub_){
			node=node->sub_;
		}else if (node->next_){
			node=node->next_;
		}else{
			while (node && !node->next_){
				node=node->up_;
			}
			if (node) node=node->next_;
		}
	}
}

Fl_ToggleTree::Fl_ToggleTree(int x,int y,int w,int h)
:Fl_Tree(x,y,w,h){
	pixmap_offset_=16;
	label_offset_=40;
	current_=0;
	state_=FL_TOGGLE_NONE;
}

int cnt=0;

#include <stdio.h>

void Fl_ToggleTree::draw_node(int depth,int cy,Fl_Node* node){
	Fl_ToggleNode* tnode=(Fl_ToggleNode*) node;
	if (damage()==FL_DAMAGE_CHILD && !tnode->changed_ && damaged_==0){
		return;
	}

	tnode->changed_=0;
	if (tnode->selected_){
		fl_color(FL_BLACK);
		fl_rectf(x(),cy+1,w(),height(node)-1);
	}else{
		fl_color((cy-y()>>4)&1?FL_WHITE:FL_LIGHT2);
		fl_rectf(x(),cy+1,w(),height(node)-1);
	}
	fl_color(FL_LIGHT1);
	fl_line(x(),cy,x()+w(),cy);
	fl_color(FL_BLACK);
	if (tnode->can_open_){
		if (tnode->opened_) 
			sOpenIcon->draw(x()+depth*16,cy+4);
		else
			sClosedIcon->draw(x()+depth*16,cy+4);
	}
	if (node->data_){
		if (tnode->selected_){
			fl_color(FL_YELLOW);
		}else{
			fl_color(FL_BLACK);
		}
		fl_font(FL_HELVETICA,12);
		Fl_ToggleNodeData* data=(Fl_ToggleNodeData*)(node->data_);
		if (data->label_){
			fl_draw(data->label_,x()+depth*16+label_offset_,cy+12);
		}
		if (data->pixmap_){
			data->pixmap_->draw(x()+depth*16+pixmap_offset_,cy+1);
		}
	}
}

void Fl_ToggleTree::open(Fl_ToggleNode* node){
	node->sub_=node->oldsub_;
	int th=total_height(node->sub_);
	node->opened_=1;
	damaged_=node;
	if (th){
		damage(FL_DAMAGE_TREE);
	}else{
		damage(FL_DAMAGE_CHILD);	
	}
	if (th){
		resize(x(),y(),w(),h()+th);
		parent()->damage(FL_DAMAGE_CHILD);
	}
}

void Fl_ToggleTree::close(Fl_ToggleNode* node){
	int th=total_height(node->sub_);
	node->opened_=0;
	node->oldsub_=node->sub_;
 	node->sub_=0;

	damaged_=node;
	if (th){
		damage(FL_DAMAGE_TREE);
		resize(x(),y(),w(),h()-th);
		parent()->damage(FL_DAMAGE_SCROLL);
	}else{
		damage(FL_DAMAGE_CHILD);
	}
}

int Fl_ToggleTree::handle(int event){
	//printf("%d\n",event);
	static Fl_ToggleNode* prev=0;
	switch (event){
		case FL_ENTER:
			return 1;
		case FL_RELEASE:
			{
				int depth;
				int cy;
				Fl_ToggleNode* tnode=(Fl_ToggleNode*) find(Fl::event_y(),depth,cy);
				if (Fl::event_x()<x()+depth*16+16){
					if (tnode->opened_){
						current_=tnode;
						state_=FL_TOGGLE_OPENED;
						do_callback();
						close(tnode);
					}else{
						current_=tnode;
						state_=FL_TOGGLE_CLOSED;
						do_callback();
						open(tnode);
					}
				}else{
					if (Fl::event_state(FL_SHIFT)){
						if (prev==0) prev=tnode;
						selectrange(prev,tnode,1);
						current_=0;
						state_=FL_TOGGLE_SELECT;
						do_callback();
					}else if (Fl::event_state(FL_CTRL)){
						if (!tnode->selected_)
							selectrange(tnode,tnode,Fl::event_state(FL_CTRL));
						else{
							tnode->selected_=0;
							tnode->changed_=1;
							tnode=0;
						}
						current_=0;
						state_=FL_TOGGLE_SELECT;
						do_callback();
					}else{
						selectrange(tnode,tnode,0);
						current_=tnode;
						state_=Fl::event_clicks() ? FL_TOGGLE_HIT : FL_TOGGLE_SELECT;
						do_callback();
					}
					damaged_=0;
					damage(FL_DAMAGE_CHILD);
					prev=tnode;
				}
			}
			break;
	}		
	return 1;
}

Fl_ToggleNode* Fl_ToggleTree::selection(void){
	if (current_==0){
		current_=(Fl_ToggleNode*) first_;
	}else{
		if (current_->sub_){
			current_=(Fl_ToggleNode*) (current_->sub_);
		}else{
			if (current_->next_){
				current_=(Fl_ToggleNode*) (current_->next_);
			}else{
				do{
					current_=(Fl_ToggleNode*) (current_->up_);
				}while (current_ && !current_->next_);
				if (current_)
					current_=(Fl_ToggleNode*) (current_->next_);
			}
		}
	}
	while (current_ && !current_->selected_){
		if (current_->sub_){
			current_=(Fl_ToggleNode*) (current_->sub_);
		}else{
			if (current_->next_){
				current_=(Fl_ToggleNode*) (current_->next_);
			}else{
				do{
					current_=(Fl_ToggleNode*) (current_->up_);
				}while (current_ && !current_->next_);
				if (current_){
					current_=(Fl_ToggleNode*) (current_->next_);
				}
			}
		}		
	}
	return current_;	
}
