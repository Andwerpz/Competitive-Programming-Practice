import requests
from bs4 import BeautifulSoup
import re

def get_plaintext_from_url(url):
    try:
        # Fetch the webpage content
        response = requests.get(url, headers={"User-Agent": "Mozilla/5.0"})
        response.raise_for_status()  # Raise an error for bad responses (4xx and 5xx)

        # Parse the HTML
        soup = BeautifulSoup(response.text, "html.parser")

        # Extract all text without HTML tags
        plaintext = soup.get_text(separator="\n", strip=True)

        return plaintext
    except requests.exceptions.RequestException as e:
        return f"Error fetching the URL: {e}"

easy_list = []
with open("problem_list.txt", "r") as file:
    lines = file.readlines()  # Reads all lines into a list
    for line in lines:
        id = line.strip()[9:]
        url = "https://archive.topcoder.com/ProblemStatement/pm/" + id
        plaintext = get_plaintext_from_url(url)
        plaintext = plaintext.replace("\n", "").replace("\r", "")
        if(not re.search("DivisionI,Level Three", plaintext) and (re.search("DivisionI", plaintext) or re.search("DivisionII", plaintext))):
            print(line.strip())


#DivisionI,Level Three
# url = "https://archive.topcoder.com/ProblemStatement/pm/10261"
# plaintext = get_plaintext_from_url(url)
# plaintext = plaintext.replace("\n", "").replace("\r", "")
# print(plaintext)
