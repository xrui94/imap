// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

fn main() {

    __imap_lib::create_server();

    __imap_lib::start_static_server();

    __imap_lib::run();
}
