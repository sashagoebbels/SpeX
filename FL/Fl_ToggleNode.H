#ifndef Fl_ToggleNode_H
#define Fl_ToggleNode_H

#include <FL/Fl_Node.H>

class Fl_Pixmap;

struct Fl_ToggleNodeData {
	char* label_;
	Fl_Pixmap* pixmap_;
};

class Fl_ToggleNode:public Fl_Node {
friend class Fl_ToggleTree;
protected:
	bool selected_;
	bool changed_;
	bool opened_;
	bool can_open_;
	Fl_Node* oldsub_;
private:
	void init(Fl_ToggleNodeData* d=0,bool can_open=true){
		oldsub_=0;
		selected_=false;
		changed_=false;
		opened_=true;
		can_open_=can_open;
		data_=d;	
	}
public:
	Fl_ToggleNode(Fl_ToggleNodeData* d=0,bool can_open=true)
	:Fl_Node(){
		init(d,can_open);
	}
	Fl_ToggleNode(char* label=0,bool can_open=true,Fl_Pixmap* pixmap=0)
	:Fl_Node(){
		Fl_ToggleNodeData *d=new Fl_ToggleNodeData;
		d->label_=label;
		d->pixmap_=pixmap;
		init(d,can_open);
	}
	char* label(void){
		Fl_ToggleNodeData *data=(Fl_ToggleNodeData*) data_;
		return data->label_;
	}
	void label(char* ptr){
		Fl_ToggleNodeData *data=(Fl_ToggleNodeData*) data_;
		data->label_=ptr;
	}
	Fl_Pixmap* pixmap(void){
		Fl_ToggleNodeData *data=(Fl_ToggleNodeData*) data_;
		return data->pixmap_;
	}
	void pixmap(Fl_Pixmap* ptr){
		Fl_ToggleNodeData *data=(Fl_ToggleNodeData*) data_;
		data->pixmap_=ptr;
	}
};

#endif

