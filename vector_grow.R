#!/usr/sbin/Rscript 

library(ggplot2)

data.vector_grow_c <- read.csv("vector_grow_c.csv", head=TRUE, sep=",")
data.vector_grow_cpp <- read.csv("vector_grow_cpp.csv", head=TRUE, sep=",")

graph <- ggplot(legend = TRUE) + 
  geom_line(data = data.vector_grow_c,  aes(x = size, y = time, colour = "C libdynamic vector")) +
  geom_line(data = data.vector_grow_cpp, aes(x = size, y = time, colour = "C++ std::vector")) +
  scale_colour_manual("", 
                      breaks = c("C libdynamic vector", "C++ std::vector"),
                      values = c("red", "blue"))
ggsave(graph, file = "vector_grow.pdf", width = 10, height = 5)
