#include<iostream>
#include<conio.h>
#include<GL/glut.h>
using namespace std;
int x, y, state, st, score, level = 0, df = 10;
int t, fl = 0, op;
static int menu_id, submenu_id;
//redraw for movement of snake -> keyboard
//check f == 1 size increase
class node
{
public:
	int j, k, p, q;
	node* next;
};
void new_prey();
class S
{
public:
	node* head, * tail;
	S()
	{
		head = new node;
		tail = new node;
		//Starting coordinates of snake
		head->p = head->j = 60;
		head->q = head->k = 40;
		tail->p = tail->j = 60;
		tail->p = tail->k = 20;
		head->next = tail;
		tail->next = NULL;
	}
	void erase(int m, int n)
	{
		glColor3f(0.0, 0.1, 0.0);
		glBegin(GL_QUADS);
		glVertex2i(m - 10, n + 10);
		glVertex2i(m - 10, n - 10);
		glVertex2i(m + 10, n - 10);
		glVertex2i(m + 10, n + 10);
		glEnd();
	}
	void redraw(int m, int n) // with update p and q according to the state (keyboard key pressed)
	{
		glBegin(GL_QUADS);
		glVertex2i(m - 10, n + 10);
		glVertex2i(m - 10, n - 10);
		glVertex2i(m + 10, n - 10);
		glVertex2i(m + 10, n + 10);
		glEnd();
	}
	bool checkStrangled(int x, int y)
	{
		int p[3];
		glReadPixels
		(
			x, y,
			1, 1,
			GL_RGB, GL_INT,
			&p[0]
		);
		//return the RGB value of the pixel x,y which is p,q
		//p[0] = R,p[1] = G, p[2] = B
		//to make the RGB value 1 where color is present and other 0 cyan - 0 1 1 ,p-> 02147483647 2147483647
		p[0] = p[0] / 2147483647;
		p[1] = p[1] / 2147483647;
		p[2] = p[2] / 2147483647;
		if (p[0] == 0 && p[1] == 1 && p[2] == 1)
			return true;
		return false;
	}
	void snake()
	{
		node* temp;
		bool b;
		int i = 1, f = 0;
		temp = head;
		while (temp != NULL && level != 0)
		{
			if (temp->next != NULL)
			{
				temp->next->p = temp->j; // j = x coord; k-> y coord
				temp->next->q = temp->k;
			}
			if (temp->next == NULL)
				erase(temp->j, temp->k);
			if (temp == head)
			{
				if (state == 1)
					temp->q += 20;
				else if (state == 2)
					temp->q -= 20;
				else if (state == 3)
					temp->p -= 20;
				else if (state == 4)
					temp->p += 20;
			}
			if (temp == head)
			{
				if (temp->j > 250 && temp->k > 590 && temp->j < 330) //upper blank space(border)
					temp->q = 20; //exit from top hollow , enter from bottom //setting q coord
				else if (temp->j > 250 && temp->k < 10 && temp->j < 330)//lower blank space(border)
					temp->q = 580;
				else if (temp->j < 10 || temp->j>590 || temp->k < 10 || temp->k>590) //Whole border
				{
					cout << "\n Crashed with wall \n!!! Game Over !!!\n";
					if (level == 1)
						cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
					if (level == 2)
						cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
					fl = 1; op = 1;
				}
				else if (temp->j > 150 && temp->j < 450 && temp->k>290 && temp->k < 330
					&& level == 2) //R1 rectangle
				{
					cout << "\n Crashed with wall \n!!! Game Over !!!\n";
					fl = 1; op = 1;
					if (level == 1)
						cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
					if (level == 2)
						cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
				}
				else if (temp->j > 270 && temp->j < 310 && temp->k>150 && temp->k < 450
					&& level == 2)//R2 rectangle
				{
					cout << "\n Crashed with wall \n!!! Game Over !!!\n";
					if (level == 1)
						cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
					if (level == 2)
						cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
					fl = 1; op = 1;
				}
				// Upper L
				else if (temp->j > 380 && temp->j < 520 && temp->k>390 && temp->k < 430
					&& level == 2)//
				{
					cout << "\n Crashed with wall \n!!! Game Over !!!\n";
					if (level == 1)
						cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
					if (level == 2)
						cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
					fl = 1; op = 1;
				}
				else if (temp->j > 380 && temp->j < 420 && temp->k>390 && temp->k < 530
					&& level == 2)//
				{
					cout << "\n Crashed with wall \n!!! Game Over !!!\n";
					if (level == 1)
						cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
					if (level == 2)
						cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
					fl = 1; op = 1;
				}
				//Lower L
				else if (temp->j > 70 && temp->j < 210 && temp->k>180 && temp->k < 220
					&& level == 2)
				{
					cout << "\n Crashed with wall \n!!! Game Over !!!\n";
					if (level == 1)
						cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
					if (level == 2)
						cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
					fl = 1; op = 1;
				}
				else if (temp->j > 170 && temp->j < 210 && temp->k>80 && temp->k < 220
					&& level == 2)
				{
					cout << "\n Crashed with wall \n!!! Game Over !!!\n";
					if (level == 1)
						cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
					if (level == 2)
						cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
					fl = 1; op = 1;
				}
			}
			//redraw
			if (temp == head)
			{
				b = checkStrangled(temp->p, temp->q);
				if (b)
				{
					cout << "\n\tStrangled\n !!! Game Over !!!\n";
					if (level == 1)
						cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
					if (level == 2)
						cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
					fl = 1; op = 1;
				}
			}
			glColor3f(0.0, 1.0, 1.0);
			if (temp == head)
				glColor3f(1, 0.4, 0); //Color of HEAD of SNAKE
			redraw(temp->p, temp->q);
			temp->j = temp->p;
			temp->k = temp->q;
			//prey_Eaten_Or_Not
			if (temp->p == (x + 10) && temp->q == y - 10) //x and y coordinated of prey
			{
				++score;
				new_prey();
				t = t - 5; // t check if you have completed the game or not ;
				if (t < 20)
				{
					if (level == 1)
						cout << "Congrats! You have completed EASY version of the challenge\n" << "\tScore : " << score * 10;
					if (level == 2)
						cout << "Congrats! You have completed HARD version of the challenge\n" << "\tScore : " << score * 10;
					cout << "\n\n##################################\n";
					cout << "##### YOU WON THIS CHALLENGE #####";
					cout << "\n##################################\n";
					fl = 1;
				}
				f = 1;
			}
			glFlush();
			temp = temp->next;
		}
		//new node
		if (f == 1) //prey eaten
		{
			node* temp1 = new node;
			temp1->j = tail->j;
			temp1->k = tail->k;
			temp1->p = tail->p;
			temp1->q = tail->q;
			temp1->next = NULL;
			tail->next = temp1;
			tail = temp1;
			//add at the end -> increase size
		}
		f = 0;
	}
};
void DisplayText(string text, int x, int y, int font)
{
	void* p = NULL;
	if (font < 8 && font>1)
		p = ((void*)font);
	else
		p = ((void*)5);
	glColor3f(0, 0, 1);
	glRasterPos2f(x, y);
	size_t len = text.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(p, (int)text[i]);
	glColor3f(0, 0, 1);
}
S saap;
void Timer(int value)
{
	saap.snake();
	if (!fl) //game over or not
		glutTimerFunc(t, Timer, 0);
	else
	{
		if (op == 1) //op =1 crashed
			DisplayText("!!! Game Over !!!", 220, 320, 5);
		else // won
			DisplayText("Congrats!! You Won", 220, 320, 5);
		glFlush();
	}
}
void boundry()
{
	//glClearColor(0.0,0.0,0.0,0.0);
	// glClear(GL_COLOR_BUFFER_BIT);
	if (level == 1)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		//leftWall
		glColor3f(1, 1, 0);
		glVertex2f(0.0, 0.0);
		glVertex2f(10.0, 0.0);
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(10.0, 600.0);
		glVertex2f(0.0, 600.0);
		//downWall
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 10.0);
		glColor3f(1, 1, 0);
		glVertex2f(250.0, 10.0);
		glVertex2f(250.0, 0.0);
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(330.0, 0.0);
		glVertex2f(330.0, 10.0);
		glColor3f(1, 1, 0);
		glVertex2f(600.0, 10.0);
		glVertex2f(600.0, 0.0);
		//rightWall
		glColor3f(1, 1, 0);
		glVertex2f(590.0, 0.0);
		glVertex2f(600.0, 0.0);
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(600.0, 600.0);
		glVertex2f(590.0, 600.0);
		//topWall
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(600.0, 600.0);
		glVertex2f(600.0, 590.0);
		glColor3f(1, 1, 0);
		glVertex2f(330.0, 590.0);
		glVertex2f(330.0, 600.0);
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(250.0, 600.0);
		glVertex2f(250.0, 590.0);
		glColor3f(1, 1, 0);
		glVertex2f(0.0, 590.0);
		glVertex2f(0.0, 600.0);
		glEnd();
		glFlush();
	}
	if (level == 2)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		//leftWall
		glColor3f(1, 1, 0);
		glVertex2f(0.0, 0.0);
		glVertex2f(10.0, 0.0);
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(10.0, 600.0);
		glVertex2f(0.0, 600.0);
		//downWall
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 10.0);
		glColor3f(1, 1, 0);
		glVertex2f(250.0, 10.0);
		glVertex2f(250.0, 0.0);
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(330.0, 0.0);
		glVertex2f(330.0, 10.0);
		glColor3f(1, 1, 0);
		glVertex2f(600.0, 10.0);
		glVertex2f(600.0, 0.0);
		//rightWall
		glColor3f(1, 1, 0);
		glVertex2f(590.0, 0.0);
		glVertex2f(600.0, 0.0);
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(600.0, 600.0);
		glVertex2f(590.0, 600.0);
		//topWall
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(600.0, 600.0);
		glVertex2f(600.0, 590.0);
		glColor3f(1, 1, 0);
		glVertex2f(330.0, 590.0);
		glVertex2f(330.0, 600.0);
		glColor3f(1, 1, 0);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(250.0, 600.0);
		glVertex2f(250.0, 590.0);
		glColor3f(1, 1, 0);
		glVertex2f(0.0, 590.0);
		glVertex2f(0.0, 600.0);
		// Plus Hurdle
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(270, 150);
		glVertex2f(310, 150);
		glColor3f(1, 0, 0.5);
		glVertex2f(310, 450);
		glVertex2f(270, 450);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(150, 290);
		glVertex2f(150, 330);
		glColor3f(1, 0, 0.5);
		glVertex2f(450, 330);
		glVertex2f(450, 290);
		//upper L
		//glColor3f(1,0,0.5);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(380, 530);
		glVertex2f(420, 530);
		glColor3f(1, 0, 0.5);
		glVertex2f(420, 390);
		glVertex2f(380, 390);
		glColor3f(1, 0, 0.5);
		//glColor3f(1.0,1.0,1.0);
		glVertex2f(380, 430);
		glVertex2f(520, 430);
		//glColor3f(1,0,0.5);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(520, 390);
		glVertex2f(380, 390);
		//lower L
		glColor3f(1, 0, 0.5);
		glVertex2f(170, 220);
		glVertex2f(210, 220);
		//glColor3f(1,0,0.5);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(210, 80);
		glVertex2f(170, 80);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(70, 220);
		glVertex2f(210, 220);
		glColor3f(1, 0, 0.5);
		glVertex2f(210, 180);
		glVertex2f(70, 180);
		glEnd();
		glFlush();
	}
}
void new_prey()
{
	//boundry();
	int i = 1;
	bool b = true;
	x = rand() % 590 + 10;
	y = rand() % 590 + 10;
	if (x >= 590 || x <= 10) // no prey at boundary
		x = 40;
	if (y <= 10 || y >= 590)
		y = 40;
	do // new prey should not be made on the snake
	{
		b = saap.checkStrangled(x, y);
		if (b)
		{
			new_prey();
			return;
		}
	} while (b);
	//Allignment
	x = x - ((x - 10) % 20); // multiple of 10s
	y = y + ((590 - y) % 20);
	if (level == 2)
	{
		if (x > 130 && x < 450) //head touches that's why 20 is subtracted
			if (y > 290 && y < 350)
				y += 40;
		if (y > 150 && y < 490) //get prey out of cross
			if (x > 250 && x < 310)
				x += 40;
		//upper L
		//horizontal
		if (x > 360 && x < 520) //head touches that's why 20 is subtracted
			if (y > 390 && y < 450)
				y += 40;
		//vertical
		if (y > 430 && y < 570) //get prey out of cross
			if (x > 360 && x < 440)
				x += 40;
		//lower L
		if (x > 50 && x < 210) //head touches that's why 20 is subtracted
			if (y > 180 && y < 240)
				y += 40;
		if (y > 80 && y < 260) //get prey out of cross
			if (x > 150 && x < 210)
				x += 40;
	}
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS); // draw prey
	glVertex2i(x, y);
	glVertex2i(x + 20, y);
	glColor3f(0.2, 0.5, 0.2);
	glVertex2i(x + 20, y - 20);
	glVertex2i(x, y - 20);
	glEnd();
	glFlush();
}
void my_display()
{
}
void my_reshape(GLsizei x, GLsizei y)
{
	glutReshapeWindow(600, 600);
}
void my_keyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		state = 1;
		break;
	case GLUT_KEY_DOWN:
		state = 2;
		break;
	case GLUT_KEY_LEFT:
		state = 3;
		break;
	case GLUT_KEY_RIGHT:
		state = 4;
		break;
	case GLUT_KEY_F1:
		exit(0);
		break;
	default:
		break;
	}
}
void menu(int num)
{
	level = num;
	boundry();
	new_prey();
	t = 140; //win after eat 25 preys
	state = 1;
	glutTimerFunc(0, Timer, 0);
	glutPostRedisplay(); //glutPostRedisplay marks the current window as needing to be redisplayed.
	glFlush();
}
void createmenu()
{
	submenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("EASY", 1);
	glutAddMenuEntry("HARD", 2);
	menu_id = glutCreateMenu(menu);
	glutAddSubMenu("Select Difficulty", submenu_id);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void myinit()
{
	srand(time(NULL));
	glClearColor(0.0, 0.1, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
}
int main(int argc, char** argv)
{
	cout << "RULES : --->\n\t* Main objective is to eat the prey.\n\t* Use UP(^),DOWN(v), RIGHT(> ), and LEFT(< ) arrow keys to move your snake.\n\t* Try neither toCRASH with the WALLS nor with your BODY.\n\t* The more you eat the prey, your score increases and the bigger you become.\n\t* You have to eat 25 preys to win the challenge.\n\n";
	cout << "After starting of the game, first right click using mouse and select the difficulty.\n";
	cout << "Press Enter key to start the game\n\n\n";
	_getch();
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Snake and Frog Game");
	glutDisplayFunc(my_display);
	glutReshapeFunc(my_reshape);
	glutSpecialFunc(my_keyboard);
	myinit();
	createmenu();
	glutMainLoop();
	return 0;
}
