using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System.Windows.Navigation;
using UIAutomation;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.

builder.Services.AddControllers().AddNewtonsoftJson(options =>
{
    //�޸��������Ƶ����л���ʽ������ĸСд
    options.SerializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();

    //�޸�ʱ������л���ʽ
    options.SerializerSettings.Converters.Add(new IsoDateTimeConverter() { DateTimeFormat = "yyyy/MM/dd HH:mm:ss" });
});

//builder.Services.AddNewtonsoftJson(options => { });

// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddUIAutomation();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseAuthorization();

app.MapControllers();

app.Run();
