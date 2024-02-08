using Newtonsoft.Json.Serialization;
using Newtonsoft.Json;
using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;

namespace KALEIDOSCOPE
{
    [AttributeUsage(AttributeTargets.Field)]
    public class HideInspector : Attribute { }

    [AttributeUsage(AttributeTargets.Field)]
    public class SerializeField : Attribute { }


    public class CustomContractResolver : DefaultContractResolver
    {
        protected override IList<JsonProperty> CreateProperties(Type type, MemberSerialization memberSerialization)
        {
            // フィールドのみを対象とする
            var fields = type.GetFields(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);

            return fields.Select(f => CreateProperty(f, memberSerialization))
                .ToList();
        }

        protected override JsonProperty CreateProperty(MemberInfo member, MemberSerialization memberSerialization)
        {
            JsonProperty property = base.CreateProperty(member, memberSerialization);
            // バックエンドフィールドの名前パターンを確認して除外
            if (member.MemberType == MemberTypes.Field && member.Name.EndsWith("k__BackingField"))
            {
                property.Ignored = true;
            }
            // プライベートフィールドにカスタムアトリビュートが適用されているかチェック
            if (member.MemberType == MemberTypes.Field && member.IsDefined(typeof(SerializeField), true))
            {
                property.Writable = true;
                property.Readable = true;
            }
            if(member.MemberType == MemberTypes.Field)
            {
                property.Writable = true; // フィールドは常に書き込み可能
                property.Readable = true; // フィールドは常に読み取り可能
            }
            else
            {
                property.Ignored = true; // プロパティは無視
            }
            return property;
        }
    }
}