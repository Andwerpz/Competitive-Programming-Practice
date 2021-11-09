//package expressionevaluationerror;

import java.util.*;
import java.io.*;

public class expressionevaluationerror {
	public static void main(String[] args) throws IOException {
		
		//1567D
		
		//first, notice that if you have a value like this: 200, it has equivalent value as this: 100 + 100. So the first thing you should do if you need more numbers is to
		//split all the digits into seperate numbers. 
		
		//if you're just left with numbers in the form of 1000...000, then you'll have to reduce them. It's optimal to reduce the lowest numbers first; reduce 10 before 100. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			char[] s = st.nextToken().toCharArray();
			int n = Integer.parseInt(st.nextToken());
			int power = 1;
			ArrayList<Integer> dict = new ArrayList<Integer>();
			for(int i = s.length - 1; i >= 0; i--) {
				if(s[i] != '0') {
					dict.add(Integer.parseInt(s[i] + "") * power);
				}
				
				power *= 10;
			}
			if(dict.size() >= n) {
				int pointer = 0;
				for(int i = 0; i < n; i++) {
					if(i != n - 1) {
						fout.append(dict.get(pointer));
						pointer ++;
					}
					else {
						int sum = 0;
						while(pointer != dict.size()) {
							sum += dict.get(pointer);
							pointer ++;
						}
						fout.append(sum);
					}
					fout.append(" ");
				}
				fout.append("\n");
			}
			else {
				ArrayList<Integer> tens = new ArrayList<Integer>();
				for(int i = 0; i < dict.size(); i++) {
					int next = dict.get(i);
					power = next / (Integer.parseInt((next + "").charAt(0) + ""));
					while(true) {
						tens.add(power);
						next -= power;
						if(next == 0) {
							break;
						}
					}
				}
				//System.out.println(tens);
				if(tens.size() >= n) {
					dict = new ArrayList<Integer>();
					dict.addAll(tens);
					int pointer = 0;
					for(int i = 0; i < n; i++) {
						if(i != n - 1) {
							fout.append(dict.get(pointer));
							pointer ++;
						}
						else {
							int sum = 0;
							while(pointer != dict.size()) {
								sum += dict.get(pointer);
								pointer ++;
							}
							fout.append(sum);
						}
						fout.append(" ");
					}
					fout.append("\n");
				}
				else {
					TreeMap<Integer, Integer> ones = new TreeMap<Integer, Integer>();
					for(int i : tens) {
						ones.put(i, ones.getOrDefault(i, 0) + 1);
					}
					int sum = tens.size();
					outer :
					while(true) {
						int next = ones.ceilingKey(2);
						ones.put(next, ones.get(next) - 1);
						if(ones.get(next) == 0) {
							ones.remove(next);
						}
						sum --;
						power = next / 10;
						while(true) {
							ones.put(power, ones.getOrDefault(power, 0) + 1);
							next -= power;
							sum ++;
							if(sum == n) {
								ones.put(power, ones.get(power) - 1);
								ones.put(next + power, ones.getOrDefault(next + power, 0) + 1);
								break outer;
							}
							if(next == 0) {
								break;
							}
						}
						//System.out.println(ones);
					}
					for(int i : ones.keySet()) {
						int amt = ones.get(i);
						for(int j = 0; j < amt; j++) {
							fout.append(i).append(" ");
						}
						
					}
					fout.append("\n");
				}
			}
		}
		System.out.print(fout);
	}
}
