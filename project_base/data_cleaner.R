library(tidyverse)

data = read.delim("routes.dat.txt", sep = ",", header = F)
data = as_tibble(data)
data2 = data |>
  filter(V3 != "\\N" & V4 != "\\N" & V5 != "\\N" & V6 != "\\N" & V8 != "\\N" & V8 == 0) |>
  select(V3, V4, V5, V6)

airports = read.delim("airports.dat.txt", sep = ",", header = F)
airports2 = airports |>
  filter(V1 != "\\N" & V2 != "\\N" & V5 != "\\N" & V6 != "\\N" & V7 != "\\N" & V8 != "\\N") |>
  select(V1, V2, V5, V6, V7, V8)

write.table(data2, "newdata.csv", quote = F, row.names = F, col.names = F)
write.table(airports2, "new_airports.csv", quote = F, row.names = F, col.names = F)

