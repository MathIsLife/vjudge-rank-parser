# vjudge-rank-parser
A parser that extracts standings data from a Virtual Judge contest page HTML code.

# How to use?
- Use "inspect element" to reveal and copy the `<body>` element of the HTML code in a contest standings page.
- Format the code using 2 spaces from this place: https://www.freeformatter.com/html-formatter.html
- Save the formatted code into a text file named "contest-X.txt" where X is the contest number (starting with 1, 2, 3, ...). For example, you should save 5 contests in files "contest-1.txt", "contest-2.txt", ..., "contest-5.txt".
- Run the parser. It will produce a file "out.txt" with the relevant data of people in sorted order according to performance (descending order of total count of solved problems, equality broken with ascending order of total time penalties). The data is printed in one column at a time so that in can be conveniently copied to a more structured place like MS Excel or Google Sheets.

# Catches
- Not totally automated.
- It can cease to work if something in the HTML code format of Virtual Judge changes in future.

