#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>
#include <memory>
#include <unordered_map>

namespace parser {
    enum class TokenType {
        /* Keywords */

        RETURN = 1,
        CLASS,
        
        /* -------- */

        /* Primitive Data Types */
        INT = 100,
        STRING,
        FLOAT,
        DOUBLE,
        /* -------------------- */

        /* SYMBOLS */
        SEMICOLON = 200,
        PERIOD,
        ASSIGN,
        EQUALS,
        MUL,
        DIV,
        PLUS,
        MINUS,
        LEFT_PAREN,
        RIGHT_PAREN,
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    static const auto keywords = std::unordered_map({
        std::make_pair(std::string_view("return"), TokenType::RETURN),
        std::make_pair(std::string_view("class"), TokenType::CLASS),
        std::make_pair(std::string_view("int"), TokenType::INT),
        std::make_pair(std::string_view("string"), TokenType::STRING),
        std::make_pair(std::string_view("float"), TokenType::FLOAT),
        std::make_pair(std::string_view("double"), TokenType::DOUBLE)
    });

    enum class AstNodeType {
        FUNCTION_DECLARATION = 1,
        VARIABLE_DECLARATION,
        CALL_EXPRESSION,
        VARIABLE_EXPRESSION,
        BLOCK,
        MEMBER_ACCESS,
        CAST,
    };

    struct DataTypeName;
    struct FunctionName;
    struct MethodName;
    struct ParameterDeclaration;
    struct FunctionDeclaration;
    struct VariableDeclaration;
    struct CallExpression;
    struct VariableExpression;
    struct BinaryExpression;
    struct MemberExpression;
    struct Block;
    struct Cast;
    struct Literal;

    using AstNode = std::variant<
        DataTypeName,
        FunctionName,
        FunctionDeclaration,
        VariableDeclaration,
        CallExpression,
        VariableExpression,
        MemberExpression,
        Block,
        Cast
    >;
    
    template<typename T, typename Variant>
    struct IsInVariant;
    
    template<typename T, typename... Types>
    struct IsInVariant<T, std::variant<Types...>> {
        static constexpr bool value = (std::is_same_v<T, Types> || ...);
    };
    
    template<typename T>
    constexpr bool is_in_astnode_v = IsInVariant<T, AstNode>::value;

    template<typename... Ts>
    using AstNodeOnlySpecified = std::enable_if_t<
        (is_in_astnode_v<Ts> && ...),
        std::variant<Ts...>
    >;

    struct DataTypeName {
        std::string name;
    };

    struct FunctionName {
        std::string name;
    };

    struct ParameterDeclaration {
        std::string name;
        DataTypeName data_type;
    };

    struct FunctionDeclaration {
        std::string name;
        std::vector<ParameterDeclaration> parameters;
        DataTypeName return_type;
    };

    struct VariableDeclaration {
        std::string name;
        DataTypeName data_type;
        std::unique_ptr<std::variant<VariableExpression, Literal, BinaryExpression>> init; // can be null
    };

    struct CallExpression {
        std::unique_ptr<AstNodeOnlySpecified<VariableExpression, MemberExpression>> function;  // может быть VariableExpression или MemberExpression
        std::vector<std::unique_ptr<AstNode>> arguments;
    };

    struct VariableExpression {
        std::string name;
    };

    struct Block {
        std::vector<std::unique_ptr<AstNode>> statements;
    };

    struct MemberExpression {
        std::unique_ptr<AstNodeOnlySpecified<CallExpression, MemberExpression, VariableExpression>> object;    
        std::string member;                 
    };

    struct Cast {
        std::unique_ptr<AstNode> expression;
        DataTypeName cast_to;
    };

    struct AstNodeBase {
        AstNodeType type;
        explicit AstNodeBase(AstNodeType t) : type(t) {}
    };

    class Parser {
        std::string code;

        std::vector<Token> 
        tokenize();

    public:
        Parser(const std::string& source);

        AstNode
        parse();
        
    };
}