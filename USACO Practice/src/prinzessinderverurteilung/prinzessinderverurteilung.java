//package prinzessinderverurteilung;

import java.util.*;
import java.io.*;

public class prinzessinderverurteilung {
	public static void main(String[] args) throws IOException {
		
		//1536B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			ArrayList<Character> test = new ArrayList<Character>();
			test.add('a');
			while(true) {
				boolean isValid = true;
				for(int i = 0; i < n - test.size() + 1; i++) {
					boolean curValid = false;
					for(int j = 0; j < test.size(); j++) {
						if(test.get(j) != s[i + j]) {
							curValid = true;
							break;
						}
					}
					isValid &= curValid;
				}
				if(isValid) {
					break;
				}
				else {
					test.set(test.size() - 1, (char) (test.get(test.size() - 1) + 1));
					for(int i = test.size() - 1; i >= 0; i--) {
						if(i == 0) {
							if(test.get(0) > 'z') {
								test.set(0, 'a');
								test.add(0, 'a');
							}
						}
						else {
							if(test.get(i) > 'z') {
								test.set(i, 'a');
								test.set(i - 1, (char) (test.get(i - 1) + 1));
							}
						}
					}
				}
			}
			String output = "";
			for(int i = 0; i < test.size(); i++) {
				output += test.get(i);
			}
			fout.append(output).append("\n");
		}
		System.out.print(fout);
	}
}
