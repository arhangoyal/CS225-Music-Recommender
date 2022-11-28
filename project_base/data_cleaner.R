library(tidyverse)
library(nycflights13)

data = read.delim("routes.dat.txt", sep = ",", header = F)
data = as_tibble(data)
data2 = data |>
  filter(V3 != "\\N" & V4 != "\\N" & V5 != "\\N" & V6 != "\\N" & V8 != "\\N")

write.table(data2, "newdata.csv", quote = F, row.names = F, col.names = F)

