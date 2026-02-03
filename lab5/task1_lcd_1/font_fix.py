import re
import sys

# Словник для транслітерації (Кирилиця -> Latin)
TRANSLIT_MAP = {
    'а': 'a', 'б': 'b', 'в': 'v', 'г': 'h', 'ґ': 'g', 'д': 'd', 'е': 'e',
    'є': 'ye', 'ж': 'zh', 'з': 'z', 'и': 'y', 'і': 'i', 'ї': 'yi', 'й': 'j',
    'к': 'k', 'л': 'l', 'м': 'm', 'н': 'n', 'о': 'o', 'п': 'p', 'р': 'r',
    'с': 's', 'т': 't', 'у': 'u', 'ф': 'f', 'х': 'kh', 'ц': 'ts', 'ч': 'ch',
    'ш': 'sh', 'щ': 'shch', 'ь': '', 'ю': 'yu', 'я': 'ya',
    'А': 'A', 'Б': 'B', 'В': 'V', 'Г': 'H', 'Ґ': 'G', 'Д': 'D', 'Е': 'E',
    'Є': 'YE', 'Ж': 'ZH', 'З': 'Z', 'И': 'Y', 'І': 'I', 'Ї': 'YI', 'Й': 'J',
    'К': 'K', 'Л': 'L', 'М': 'M', 'Н': 'N', 'О': 'O', 'П': 'P', 'Р': 'R',
    'С': 'S', 'Т': 'T', 'У': 'U', 'Ф': 'F', 'Х': 'KH', 'Ц': 'TS', 'Ч': 'CH',
    'Ш': 'SH', 'Щ': 'SHCH', 'Ь': '', 'Ю': 'YU', 'Я': 'YA'
}

def get_visual_comment(binary_string: str) -> str:
    """Генерує візуалізацію: 1 -> '*', 0 -> '.'"""
    visual = "".join("*" if bit == '1' else "." for bit in binary_string)
    return f" // {visual}"

def extract_binary_data(raw_text: str) -> list:
    """Шукає всі входження Bxxxxxx або 0bxxxxxx."""
    matches = re.findall(r'\b(?:B|0b)([01]+)', raw_text)
    return matches

def make_safe_var_name(user_input: str) -> str:
    """Створює безпечну назву змінної з транслітерацією."""
    transliterated = ""
    for char in user_input:
        transliterated += TRANSLIT_MAP.get(char, char)
    
    safe_name = re.sub(r'[^a-zA-Z0-9]', '_', transliterated)
    safe_name = re.sub(r'_+', '_', safe_name).strip('_')
    
    if not safe_name:
        return "UNKNOWN_CHAR"
    
    return f"GLYPH_{safe_name}"

def generate_cpp_code(char_name_input: str, binary_list: list) -> str:
    """Генерує готовий C++ код."""
    var_name = make_safe_var_name(char_name_input)

    output = []
    output.append(f"// Літера '{char_name_input}'")
    output.append(f"const uint8_t {var_name}[] PROGMEM = {{")
    
    for i, bits in enumerate(binary_list):
        std_binary = f"0b{bits}"
        visual = get_visual_comment(bits)
        comma = "," if i < len(binary_list) - 1 else " "
        line = f"  {std_binary}{comma} {visual}"
        output.append(line)
        
    output.append("};")
    return "\n".join(output)

def main():
    print("-" * 60)
    print("ГЕНЕРАТОР ШРИФТІВ")
    print("-" * 60)
    
    # Крок 1
    print("1. Введіть літеру (наприклад 'и', 'Ж' або 'smile'):")
    char_name = input("> ").strip()
    if not char_name: char_name = "Unknown"
    
    # Крок 2
    print("\n2. Створіть літеру на сайті:")
    print("   https://maxpromer.github.io/LCD-Character-Creator/")
    
    # Крок 3
    print("\n3. Вставте код із сайту сюди і натисніть Enter двічі:")
    
    lines = []
    while True:
        try:
            line = input()
            if not line: break # Порожній рядок = кінець вводу
            lines.append(line)
        except EOFError:
            break
            
    raw_text = "\n".join(lines)
    binary_data = extract_binary_data(raw_text)
    
    print("\n" + "="*30)
    if binary_data:
        print(generate_cpp_code(char_name, binary_data))
    else:
        print("[ПОМИЛКА] Код не знайдено.")
    print("="*30)
    # Тут немає input(), скрипт завершується одразу

if __name__ == "__main__":
    main()