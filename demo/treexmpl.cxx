#include <FL/Fl_ToggleTree.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl.H>

#include <FL/folder_small.xpm>
#include <FL/file_small.xpm>

#include <stdio.h>

void test_callback(Fl_Widget* w,void* ptr){
	Fl_ToggleTree* t=(Fl_ToggleTree*) w;
	
	printf("state: %d\n",
		t->state()
	);
	
	if (t->current()){
		printf("current=%s\n",t->current()->label());	
	}else{
		// if current()==0 then we have a multiple selecting
		printf("MULTIPLE:\n");
		Fl_ToggleNode* s;
		while ((s=t->selection())){
			printf(" selected=%s\n",s->label());
		}
	}
	
}

main(){
	Fl_Window w(220,200,"Tree Example");
	Fl_Scroll s(10,10,200,180);
	s.type(Fl_Scroll::VERTICAL_ALWAYS);
	Fl_ToggleTree t(10,10,200-s.scrollbar.w(),0);	
	/* When constructing a Fl_ToggleTree, the 
	   height doesn't matter, because we will 
	   call
		t.update_height();
	   anyway after building the tree.
	*/

	t.callback(test_callback); 
	/* The callback for a Fl_ToggleTree is called
	   when open/close/select/unselect node.
	   TODO: proper implementation of when() 
	*/

	Fl_Pixmap* folderSmall=new Fl_Pixmap(folder_small);
	Fl_Pixmap* fileSmall  =new Fl_Pixmap(file_small);

	Fl_ToggleNode* n2;
	/* We build a example tree using Fl_TreeBuilder. */
	Fl_TreeBuilder b(n2=new Fl_ToggleNode("aaa",1,folderSmall));

	t.start(n2); /* Set it as the first node of the Fl_ToggleTree. */

	/* Add some nodes, some open, some closed, with icons.*/
	/* Fl_ToggleNode::Fl_ToggleNode( LABEL , CAN_OPEN (default=1) , ICON )
	*/
	
	b.next(n2=new Fl_ToggleNode("bbb",1,folderSmall));
	b.sub(new Fl_ToggleNode("ccc",1,folderSmall));
	b.sub(new Fl_ToggleNode("ddd",0,fileSmall));
	t.close(n2); /* By default, nodes are open. Close them explicitely. */
	b.up();
	b.up();
	b.next(new Fl_ToggleNode("eee",1,folderSmall));
	b.sub(new Fl_ToggleNode("fff",0,fileSmall));
	b.up();
	b.next(new Fl_ToggleNode("ggg",1,folderSmall));
	b.sub(new Fl_ToggleNode("hhh",1,folderSmall));
	t.close(n2); /* By default, nodes are open. Close them explicitely. */
	b.sub(new Fl_ToggleNode("iii",1,folderSmall));
	b.up();
	b.up();
	b.next(new Fl_ToggleNode("jjj",1,folderSmall));
	b.sub(new Fl_ToggleNode("kkk",0,fileSmall));
	b.up();
	b.next(new Fl_ToggleNode("lll",0,fileSmall));
	b.next(new Fl_ToggleNode("mmm",1,folderSmall));
	t.close(n2); /* By default, nodes are open. Close them explicitely. */
	b.sub(new Fl_ToggleNode("nnn",1,folderSmall));
	b.sub(new Fl_ToggleNode("ooo",0,fileSmall));
	b.up();
	b.up();
	b.next(new Fl_ToggleNode("ppp",1,folderSmall));
	b.sub(new Fl_ToggleNode("qqq",0,fileSmall));
	b.up();
	b.next(new Fl_ToggleNode("rrr",1,folderSmall));
	b.sub(new Fl_ToggleNode("sss",1,folderSmall));
	b.sub(new Fl_ToggleNode("ttt",1,folderSmall));
	b.up();
	b.up();
	b.next(new Fl_ToggleNode("uuu",1,folderSmall));
	b.sub(new Fl_ToggleNode("vvv",0,fileSmall));
	b.up();
	b.next(new Fl_ToggleNode("www",0,fileSmall));
	b.next(new Fl_ToggleNode("xxx",0,fileSmall));
	b.next(new Fl_ToggleNode("yyy",0,fileSmall));
	b.sub(new Fl_ToggleNode("zzz",0,fileSmall));
	
	t.update_height();
	/* calculate the initial height of the tree */
	
	w.show();
	Fl::run();
}


