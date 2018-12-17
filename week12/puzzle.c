#include "jrb_dgraph.h"
#include "libfdr/dllist.h"
#include "libfdr/jrb.h"
#define SIZE 3

typedef struct puzzle{
	int matrix[SIZE][SIZE];
	int x;
	int y;
}PuzzleState;

int compare_state(PuzzleState a, PuzzleState b){
	int i, j;
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			if(a.matrix[i][j] != b.matrix[i][j])
				return 0;
		}
	}
	return 1;
}

int check_valid_state(PuzzleState state){

}

int move_up(PuzzleState *state){
	int x = state->x;
	int y = state->y;
	int new_x = x;
	int new_y = y - 1;
	//SUCCESS
	if(new_y >= 0 && new_y < SIZE){
		state->x = new_x;
		state->y = new_y;
		return 1;
	}
	//FAIL
	return 0;
}

int move_down(PuzzleState *state){
	int x = state->x;
	int y = state->y;
	int new_x = x;
	int new_y = y + 1;
	//SUCCESS
	if(new_y >= 0 && new_y < SIZE){
		state->x = new_x;
		state->y = new_y;
		return 1;
	}
	//FAIL
	return 0;
}

int move_left(PuzzleState *state){
	int x = state->x;
	int y = state->y;
	int new_x = x - 1;
	int new_y = y;
	//SUCCESS
	if(new_x >= 0 && new_x < SIZE){
		state->x = new_x;
		state->y = new_y;
		return 1;
	}
	//FAIL
	return 0;
}

int move_right(PuzzleState *state){
	int x = state->x;
	int y = state->y;
	int new_x = x + 1;
	int new_y = y;
	//SUCCESS
	if(new_x >= 0 && new_x < SIZE){
		state->x = new_x;
		state->y = new_y;
		return 1;
	}
	//FAIL
	return 0;
}

int check_visited(Dllist closed, PuzzleState state){
	Dllist dll_ptr;
	dll_traverse(dll_ptr, closed){
		PuzzleState X = *((PuzzleState *)jval_v(dll_ptr->val));
		if(compare_state(X, state) == 1)
			return 1;
	}
	return 0;
}

int DFS(PuzzleState start, PuzzleState stop, PuzzleState *path){
	Dllist open = new_dllist();
	Dllist closed = new_dllist();

	PuzzleState *state = (PuzzleState *)malloc(sizeof(PuzzleState));
	*state = start;

	//push start state to open stack
	dll_prepend(open, new_jval_v(state));
	while(!dll_empty(open)){
		//pop open
		Dllist dll_ptr = dll_first(open);
		PuzzleState X = *((PuzzleState *)jval_v(dll_ptr->val));
		dll_delete_node(dll_ptr);

		//push X to closed
		dll_prepend(closed, new_jval_v(X));

		//generate children
		PuzzleState X_moveup = *X;
		int move_status = move_up(X_moveup);
		if(move_status == 1){
			if(check_visited(closed, X_moveup) == 0){
				if(check_visited(open, X_moveup) == 0)
					dll_prepend(open, new_jval_v(&X_moveup));
			}
		}

		PuzzleState X_movedown = *X;
		int move_status = move_down(X_movedown);
		if(move_status == 1){
			if(check_visited(closed, X_movedown) == 0){
				if(check_visited(open, X_movedown) == 0)
					dll_prepend(open, new_jval_v(&X_movedown));
			}
		}

		PuzzleState X_moveleft = *X;
		int move_status = move_left(X_moveleft);
		if(move_status == 1){
			if(check_visited(closed, X_moveleft) == 0){
				if(check_visited(open, X_moveleft) == 0)
					dll_prepend(open, new_jval_v(&X_moveleft));
			}
		}

		PuzzleState X_moveright = *X;
		int move_status = move_right(X_moveright);
		if(move_status == 1){
			if(check_visited(closed, X_moveright) == 0){
				if(check_visited(open, X_moveright) == 0)
					dll_prepend(open, new_jval_v(&X_moveright));
			}
		}
	}
}