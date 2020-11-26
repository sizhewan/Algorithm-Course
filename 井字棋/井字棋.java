//玩家为o，电脑为x
package TicTacToe;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.border.*;
public class TicTacToe  extends JApplet
{
	private cell[][] cells=new cell[3][3];
	private JLabel jlbstatus=new JLabel("O's turn to play");
	private char whosTurn='O';
	private int x,y;
	public void start()
	{
		JPanel p=new JPanel(new GridLayout(3,3,0,0));
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
               p.add(cells[i][j]=new cell());
		p.setBorder(new LineBorder(Color.red,1));
		jlbstatus.setBorder(new LineBorder(Color.yellow,1));
		setLayout(new BorderLayout());
		add(p,BorderLayout.CENTER);
		add(jlbstatus,BorderLayout.SOUTH);
	}
	public boolean isFull()
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
			{
				if(cells[i][j].getToken()==' ')
					return false;
			}
		return true;
	}
	//规定 player=1为AI -1为人类
	public int IsWin(int chessboard[][])
	{
		for (int i = 0; i<3; i++)
		{
			if (chessboard[i][0] == 1 && chessboard[i][1] == 1 && chessboard[i][2] == 1)
				return 1;
			if (chessboard[i][0] == -1 && chessboard[i][1] == -1 && chessboard[i][2] == -1)
				return -1;
		}
		for (int i = 0; i < 3; i++)
		{
			if (chessboard[0][i] == 1 && chessboard[1][i] == 1 && chessboard[2][i] == 1)
				return 1;
			if (chessboard[0][i] == -1 && chessboard[1][i] == -1 && chessboard[2][i] == -1)
				return -1;
		}
		if ((chessboard[0][0] == 1 && chessboard[1][1] == 1 && chessboard[2][2] == 1) || (chessboard[2][0] == 1 && chessboard[1][1] == 1 && chessboard[0][2] == 1))
			return 1;
		if ((chessboard[0][0] == -1 && chessboard[1][1] == -1 && chessboard[2][2] == -1) || (chessboard[2][0] == -1 && chessboard[1][1] == -1 && chessboard[0][2] == -1))
			return -1;
		return 0;
	}
	public boolean isWon(char token)
	{
		for(int i=0;i<3;i++)
		      if(cells[i][0].getToken()==token && cells[i][1].getToken()==token && cells[i][2].getToken()==token)
		    	  return true;
		for(int j=0;j<3;j++)
		      if(cells[0][j].getToken()==token && cells[1][j].getToken()==token && cells[2][j].getToken()==token)
		          return true;
		if(cells[0][0].getToken()==token && cells[1][1].getToken()==token && cells[2][2].getToken()==token)
		          return true;
		if(cells[0][2].getToken()==token && cells[1][1].getToken()==token && cells[2][0].getToken()==token)
		          return true;
		return false;
	}
	public int get_value(int chessboard[][])
	{
		int tmpQP[][]=new int [3][];
		tmpQP[0]=new int[3];
		tmpQP[1]=new int[3];
		tmpQP[2]=new int[3];
		boolean flag = true;
		for (int i = 0; i<3; i++)
			for (int j = 0; j<3; j++)
				if (chessboard[i][j] == 0)
					flag = false;
		if (flag)
			return -1001;
		if (IsWin(chessboard) == -1)
			return -1000;
		if (IsWin(chessboard) == 1)
			return 1000;
		int count = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (chessboard[i][j] == 0)
					tmpQP[i][j] = 1;
				else
					tmpQP[i][j] = chessboard[i][j];
		for (int i = 0; i<3; i++)
			count += (tmpQP[i][0] + tmpQP[i][1] + tmpQP[i][2]) / 3;
		for (int i = 0; i<3; i++)
			count += (tmpQP[0][i] + tmpQP[1][i] + tmpQP[2][i]) / 3;
		count += (tmpQP[0][0] + tmpQP[1][1] + tmpQP[2][2]) / 3;
		count += (tmpQP[2][0] + tmpQP[1][1] + tmpQP[0][2]) / 3;
		for (int i = 0; i<3; i++)
			for (int j = 0; j<3; j++)
				if (chessboard[i][j] == 0)
					tmpQP[i][j] = -1;
				else
					tmpQP[i][j] = chessboard[i][j];
		for (int i = 0; i<3; i++)
			count += (tmpQP[i][0] + tmpQP[i][1] + tmpQP[i][2]) / 3;
		for (int i = 0; i<3; i++)
			count += (tmpQP[0][i] + tmpQP[1][i] + tmpQP[2][i]) / 3;
		count += (tmpQP[0][0] + tmpQP[1][1] + tmpQP[2][2]) / 3;
		count += (tmpQP[2][0] + tmpQP[1][1] + tmpQP[0][2]) / 3;
		return count;
	}
	public int AlphaBeta(int chessboard[][], int depth, int alpha, int beta,int player)
	{
		if (depth == 0 || IsWin(chessboard)!=0)
		{
			return get_value(chessboard);
		}
		for (int i=0;i<3;i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (chessboard[i][j] == 0)
				{
					chessboard[i][j] = player;
					int val = -AlphaBeta(chessboard, depth - 1, -beta, -alpha, -player);
					chessboard[i][j] = 0;
					if (val >= beta)
						return val;
					if (val > alpha)
					{
						alpha = val;
						if (depth == 2)
						{
							x = j;
							y = i;
						}
					}
				}
			}
		}
		return alpha;
	}
	class cell extends JPanel
	{   //是类TicTacToe的内部类
		private char token=' ';
		public cell()
		{
			setBorder(new LineBorder(Color.black,1));
		    addMouseListener(new myMouseListener());
		}
		public char getToken()
		{
			return token;
		}
		public void setToken(char c)
		{
		    token=c;    
		    repaint();
		}
		public void paint(Graphics g)
		{
			super.paint(g);
		    if(token=='X')
		    {
		    	g.drawLine(10, 10, getWidth()-10, getHeight()-10);
		    	g.drawLine(getWidth()-10, 10, 10, getHeight()-10);
		    }
		    if(token=='O')
		    	g.drawOval(10,10,getWidth()-10, getHeight()-10);
		}
		class myMouseListener extends MouseAdapter
		{//是类cell的内部类
			public void mouseClicked(MouseEvent e)
			{
				if((token==' ')&&(whosTurn!=' '))
					setToken(whosTurn);
			    if(isWon('O'))
			    {
			    	jlbstatus.setText("O won!,gameover!");
			        whosTurn=' ';
			    }
			    else if(isFull())
			    {
			    	jlbstatus.setText("gameover!");
			        whosTurn=' ';
			    }
			    else
			    {
			    	int chessboard[][]=new int[3][];
			    	for(int i=0;i<3;i++)
						chessboard[i]=new int[3];
					for(int i=0;i<3;i++)
						for(int j=0;j<3;j++)
						{
							if(cells[i][j].getToken()=='X')
								chessboard[i][j]=1;
							else if(cells[i][j].getToken()=='O')
								chessboard[i][j]=-1;
							else
								chessboard[i][j]=0;
						}
					AlphaBeta(chessboard,2,-10000,10000,1);
					for(int i=0;i<3;i++)
					{
						for(int j=0;j<3;j++)
							System.out.print(chessboard[i][j]+"  ");
						System.out.println();
					}
					cells[y][x].setToken('X');
					if(isWon('X'))
				    {
				    	jlbstatus.setText("X won!,gameover!");
				        whosTurn=' ';
				    }
			    }
			}
		}
	}
}
