//package distinctcharactersqueries;

import java.util.*;
import java.io.*;

public class distinctcharactersqueriesver1 {
	
	static ArrayList<ArrayList<Node>> tree;
	static char[] s;
	
	static StreamTokenizer in;
	static int nextInt() throws IOException{
		in.nextToken();
		return (int)in.nval;
	}
	
	static String nextString() throws IOException {
		in.nextToken();
		return in.sval;
	}
	
	public static int getDistinctCharacters(int low, int high) {
		Node total = new Node();
		for(int i = low; i <= high; i += 0) {
			int index = i;
			int layer = 0;
			int increment = 1;
			while(true) {
				int temp = index;
				index /= 2;
				layer ++;
				increment *= 2;
				int l = index * 2;
				int h = index * 2 + increment;
				if(l < low || h > high) {
					index = temp;
					increment /= 2;
					layer --;
					break;
				}
			}
			total.addAll(tree.get(layer).get(index));
			i += increment;
			//System.out.println(total);
		}
		int ans = 0;
		for(int i = 0; i < 26; i++) {
			if(total.dict[i] != 0) {
				ans ++;
			}
		}
		return ans;
	}
	
	public static void setCharacter(int pos, char val) {
		char replacing = s[pos];
		s[pos] = val;
		int index = pos;
		int replaceId = replacing -'a';
		int valId = val - 'a';
		for(int i = 0; i < tree.size(); i++) {
			tree.get(i).get(index).dict[valId] ++;
			tree.get(i).get(index).dict[replaceId] --;
//			tree.get(i).get(index).dict.put(val, tree.get(i).get(index).dict.getOrDefault(val, 0) + 1);
//			tree.get(i).get(index).dict.put(replacing, tree.get(i).get(index).dict.get(replacing) - 1);
//			if(tree.get(i).get(index).dict.get(replacing) == 0) {
//				tree.get(i).get(index).dict.remove(replacing);
//			}
			index /= 2;
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//there is a far easier solution using tree sets
		
		in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
		s = nextString().toCharArray();
		int n = s.length;
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log10(n) / Math.log10(2)));
		tree = new ArrayList<ArrayList<Node>>();
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			char next = '/';
			if(i < n) {
				next = s[i];
			}
			int nextId = next - 'a';
			while(true) {
				if(tree.size() == layer) {
					tree.add(new ArrayList<Node>());
				}
				if(layer == 0) {
					Node a = new Node();
					if(next != '/') {
						a.dict[nextId] ++;
					}
					tree.get(layer).add(a);
				}
				else {
					Node a = new Node();
					int size = tree.get(layer - 1).size();
					a.addAll(tree.get(layer - 1).get(size - 1));
					a.addAll(tree.get(layer - 1).get(size - 2));
					tree.get(layer).add(a);
				}
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					break;
				}
			}
		}
		//System.out.println(tree);
		StringBuilder fout = new StringBuilder();
		int q = nextInt();
		for(int i = 0; i < q; i++) {
			int type = nextInt();
			if(type == 1) {
				int pos = nextInt() - 1;
				char val = nextString().charAt(0);
				setCharacter(pos, val);
				//System.out.println(tree);
			}
			else {
				int low = nextInt() - 1;
				int high = nextInt() - 1;
				fout.append(getDistinctCharacters(low, high)).append("\n");
			}
		}
		System.out.print(fout);
	}
	
	
}

class Node {
		
	public int[] dict;
	
	public Node() {
		dict = new int[26];
	}
	
	public void addAll(Node a) {
		for(int i = 0; i < dict.length; i++) {
			this.dict[i] += a.dict[i];
		}
	}
	
	public String toString() {
		return dict.toString() + " ";
	}
	
}
