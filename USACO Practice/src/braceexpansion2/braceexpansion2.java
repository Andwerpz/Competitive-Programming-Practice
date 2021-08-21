package braceexpansion2;

import java.util.*;
import java.io.*;

class Solution {
    public List<String> braceExpansionII(String expression) {
    	
    	//1096 Leet Code
    	
    	//this one was a pain, but it did make me think differently about expression parsing. Recursion is king, then go for a stack based approach.
    	//first, check if there are any commas on the base level. If not, then parse in the brackets as separate expressions. Commas add combinations to 
    	//the answer, touching brackets multiply combinations. Always simplify layer by layer. 
    	
        //System.out.println(expression);
        List<String> ans = new ArrayList<String>();
        char[] e = expression.toCharArray();
        ArrayList<String> nextExp = new ArrayList<String>();
        int pointer = 0;
        int numBraces = 0;
        for(int i = 0; i < e.length; i++){
            if(e[i] == '{'){
                numBraces ++;
            }
            else if(e[i] == '}'){
                numBraces --;
            }
            else if(e[i] == ',' && numBraces == 0){
                nextExp.add(expression.substring(pointer, i));
                pointer = i + 1;
            }
        }
        nextExp.add(expression.substring(pointer, e.length));
        //System.out.println(nextExp);
        if(nextExp.size() == 1){    //parsing brackets
            ans.add("");
            numBraces = 0;
            String next = "";
            for(int i = 0; i < e.length; i++){
                if(e[i] == '{'){
                    if(numBraces != 0){
                        next += e[i];
                    }
                    numBraces ++;
                }
                else if(e[i] == '}'){
                    numBraces --;
                    if(numBraces != 0){
                        next += e[i];
                    }
                    if(numBraces == 0){
                        List<String> nextAns = braceExpansionII(next);
                        next = "";
                        ArrayList<String> replace = new ArrayList<String>();
                        for(int j = 0; j < ans.size(); j++){
                            String original = ans.get(j);
                            for(int k = 0; k < nextAns.size(); k++){
                                replace.add(original + nextAns.get(k));
                            }
                        }
                        ans = replace;
                    }
                }
                else if(e[i] != '{' && e[i] != '}'){
                    if(numBraces >= 1){
                        next += e[i];
                    }
                    else{
                        for(int j = 0; j < ans.size(); j++){
                            ans.set(j, ans.get(j) + e[i]);
                        }
                    }
                }
            }
        }
        else{
            for(int i = 0; i < nextExp.size(); i++){
                List<String> nextAns = braceExpansionII(nextExp.get(i));
                ans.addAll(nextAns);
            }
        }
        HashSet<String> removeDupes = new HashSet<String>();
        removeDupes.addAll(ans);
        ans = new ArrayList<String>();
        ans.addAll(removeDupes);
        ans.sort((a, b) -> a.compareTo(b));
        return ans;
    }
}