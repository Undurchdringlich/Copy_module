const addon = require('bindings')('addon');

const files = ['D:\\Programming\\test\\text.txt', 'D:\\Programming\\test\\image.jpg'];//, "D:\\Programming\\test\\win10-64bit-radeon-software-adrenalin-2019-edition-19.10.1-oct17.exe", "D:\\Programming\\test\\code.exe", "D:\\Programming\\test\\data3.bin"]; // Пример массива путей к файлам

const location = 'D:\\Programming\\location'; // Пример папки, в которую нужно скопировать файлы

function printProgress(text) {
    console.log(text);
} // Функция callback, выводящая информацию о скопированном файле. Пример text – “Файл C:\\files\\text.txt скопирован”.

function printSuccess(text) {
    console.log(text);
} // Функция callback, выводящая сообщение о завершении копирования

addon.copy(files, location, printProgress, printSuccess);
