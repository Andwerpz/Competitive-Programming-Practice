package removeadjacent;

import java.util.*;
import java.io.*;

public class removeadjacentver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		ArrayList<Entry> groups = new ArrayList<Entry>();
		groups.add(new Entry(s[0], 0));
		for(int i = 0; i < n; i++) {
			char next = s[i];
			if(groups.get(groups.size() - 1).c != next) {
				groups.add(new Entry(next, 0));
			}
			groups.get(groups.size() - 1).n ++;
		}
		int ans = 0;
		for(char i = 'z'; i >= 'a'; i--) {
			//System.out.println(groups);
			for(int j = 0; j < groups.size(); j++) {
				if(groups.get(j).c == i && j != 0 && groups.get(j).c == (char) (groups.get(j - 1).c + 1)) {
					ans += groups.get(j).n;
					groups.remove(j);
					j--;
				}
				else if(groups.get(j).c == i && j != groups.size() - 1 && groups.get(j).c == (char) (groups.get(j + 1).c + 1)) {
					ans += groups.get(j).n;
					groups.remove(j);
					j--;
				}
			}
			for(int j = groups.size() - 1; j >= 0; j --) {
				if(j != 0 && groups.get(j).c == groups.get(j - 1).c) {
					groups.get(j - 1).n += groups.get(j).n;
					groups.remove(j);
				}
			}
		}
		System.out.println(ans);
	}
}

class Entry {
	public char c;
	public int n;
	public Entry(char c, int n) {
		this.c = c;
		this.n = n;
	}
	public String toString() {
		return c + ", " + n + "|";
	}
}