//package treelabeling;

import java.util.*;
import java.io.*;

public class treelabeling {
	public static void main(String[] args) throws IOException {
		
		//1605D
		
		//notice that for the condition u xor v <= min(u, v) to be true, the largest bit of both u and v have to be the same.
		//thus, given n, we can generate categories of numbers that when we pull two numbers out of that category, the largest bit will always be the same. 
		
		//it also holds that if the largest bit of u and v are different, then the condition is always false. So using our categories, we can
		//also say that if we were to pick two numbers from different categories, then the condition will never be true. 
		
		//lets say we were to color the tree with 2 colors, so that no two nodes of the same color are connected. This is always possible, since 
		//the graph is a tree. Count the number of nodes in one color. Is it possible to get the sum of a set of categories, so that it is equal 
		//to the amount of nodes in that category?
		
		//notice that the sizes of our categories are strictly powers of 2, except for the last category. The size of the last category doeesn't matter though, since
		//if the sum is bigger than the size of that category, we can just use the last one in our sum, and if it is smaller, then we exclude it. 
		//Thus, we can always make a sum of categories that is exactly equal to the amount of nodes of one color. 
		
		//what happens if we assign the nodes of that color with the nodes in the categories which sum is equal to the amount of nodes of that color?
		//all the nodes of that color aren't touching, and the remaining nodes are guaranteed to be in a different category than the nodes we have already placed. 
		
		//this means that according to the rules of the game, you can't move from one node to another node, which means that the first player always wins,
		//no matter which node they start on.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			int[] nodeColors = new int[n];
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < n - 1; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				int u = Integer.parseInt(st.nextToken()) - 1;
				int v = Integer.parseInt(st.nextToken()) - 1;
				c.get(u).add(v);
				c.get(v).add(u);
			}
			Stack<Integer> s = new Stack<Integer>();
			Stack<Integer> sColor = new Stack<Integer>();
			boolean[] v = new boolean[n];
			s.add(0);
			sColor.add(0);	//0 and 1
			v[0] = true;
			int numRed = 0;
			while(s.size() != 0) {	//coloring nodes into red and blue
				int cur = s.pop();
				int curColor = sColor.pop();
				if(curColor == 0) {
					numRed ++;
				}
				nodeColors[cur] = curColor;
				for(int i : c.get(cur)) {
					if(!v[i]) {
						s.add(i);
						sColor.add(curColor == 0? 1 : 0);
						v[i] = true;
					}
				}
			}
//			for(int i : nodeColors) {
//				System.out.print(i + " ");
//			}
//			System.out.println();
			ArrayList<Pair<Integer, Integer>> categories = new ArrayList<Pair<Integer, Integer>>();
			int pointer = 1;
			int sum = 0;
			while(true) {	//generating categories
				if(sum + pointer >= n) {
					categories.add(new Pair<Integer, Integer>(n - sum, sum + 1));
					break;
				}
				categories.add(new Pair<Integer, Integer>(pointer, sum + 1));
				sum += pointer;
				pointer *= 2;
			}
			categories.sort((a, b) -> -Integer.compare(a.first(), b.first()));
			//System.out.println(categories);
			Stack<Pair<Integer, Integer>> red = new Stack<>();
			Stack<Pair<Integer, Integer>> blue = new Stack<>();
			for(Pair<Integer, Integer> i : categories) {	//selecting which categories go to which color
				if(numRed - i.first() >= 0) {
					numRed -= i.first();
					red.add(i);
				}
				else {
					blue.add(i);
				}
			}
			//System.out.println(red + " " + blue);
			if(n == 1) {
				fout.append("1\n");
			}
			else {
				Pair<Integer, Integer> nextRed = red.pop();
				int rPointer = nextRed.second();
				int rEnd = rPointer + nextRed.first();
				Pair<Integer, Integer> nextBlue = blue.pop();
				int bPointer = nextBlue.second();
				int bEnd = bPointer + nextBlue.first();
				//System.out.println(rPointer + " " + rEnd + " " + bPointer + " " + bEnd);
				for(int i = 0; i < n; i++) {	//printing answers
					if(nodeColors[i] == 0) {
						fout.append(rPointer).append(" ");
						rPointer ++;
						if(rPointer == rEnd && red.size() != 0) {
							nextRed = red.pop();
							rPointer = nextRed.second();
							rEnd = rPointer + nextRed.first();
						}
					}
					else {
						fout.append(bPointer).append(" ");
						bPointer ++;
						if(bPointer == bEnd && blue.size() != 0) {
							nextBlue = blue.pop();
							bPointer = nextBlue.second();
							bEnd = bPointer + nextBlue.first();
						}
					}
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}

class Pair<T1, T2> {
	T1 p1;
	T2 p2;
	
	Pair(T1 p1, T2 p2) {
		this.p1 = p1;
		this.p2 = p2;
	}
	
	public T1 first() {
		return p1;
	}
	
	public T2 second() {
		return p2;
	}
	
	public String toString() {
		return "[" + p1 + ", " + p2 + "]";
	}
}
