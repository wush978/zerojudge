size <- c(10, 12, 14)
n <- 20
zero_position <- sample(1:3,1000,TRUE)
Spa <- matrix(NA,n,3)
for (i in 1:n)
{
  Spa[i,zero_position[i]] <- 0
  if (zero_position[i] == 1) 
  {
    Spa[i,2] <- sample(1:size[2],1)
    Spa[i,3] <- sample(1:size[3],1)
  }
  if (zero_position[i] == 2) 
  {
    Spa[i,1] <- sample(1:size[1],1)
    Spa[i,3] <- sample(1:size[3],1)
  }
  if (zero_position[i] == 3) 
  {
    Spa[i,1] <- sample(1:size[1],1)
    Spa[i,2] <- sample(1:size[2],1)
  }
}

test_data <- c()
test_data[1] <- "1"
test_data[2] <- paste(size,collapse=" ")
test_data[3] <- paste(n)
for (i in 1:n)
{
  test_data[length(test_data)+1] <- paste(Spa[i,],collapse=" ")
}
write(test_data,file="test.txt")

#--

tower <- array(1,size)
for (i in 1:n)
{
  if (Spa[i,1] == 0)
  {
    tower[,Spa[i,2],Spa[i,3]] <- 0    
  }
  if (Spa[i,2] == 0)
  {
    tower[Spa[i,1],,Spa[i,3]] <- 0    
  }
  if (Spa[i,3] == 0)
  {
    tower[Spa[i,1],Spa[i,2],] <- 0    
  }
}
sum(tower)
