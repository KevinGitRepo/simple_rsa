FROM ubuntu:latest AS build

RUN apt-get update && apt-get install -y \ 
    build-essential \ 
    libgmp-dev \ 
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY key.cpp key.h rsa.h .

RUN g++ -o key key.cpp -lgmpxx -lgmp -static

FROM scratch

COPY --from=build /app/key /key

CMD ["/key"]
