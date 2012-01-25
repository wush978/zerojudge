setwd("~/git-project/zerojudge/a324")
code <- readLines("origin-code.txt")

code <- unlist(strsplit(code, "\t"))
code <- code[grep("[[:upper:]]", code)]
code <- gsub(pattern="[[:space:]]", replacement="",x=code)
code <- substr(code, 2, nchar(code))
code <- paste("\"", code, "\"", collapse=",", sep="")
write(code, file="code.txt")

