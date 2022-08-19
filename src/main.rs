use tokio::net::{TcpListener, TcpStream};

use std::io;

#[tokio::main]
async fn main() {
    let listener = match TcpListener::bind(format!("127.0.0.1:{}", 25565)).await {
        Ok(n) => n,
        Err(e) => {
            panic!("Could not bind to port {}", 25565);
        }
    };

    loop {
        let (socket, _) = listener.accept().await.unwrap();

        println!("Client connected");

        tokio::spawn(async move {

        });
    }

}
